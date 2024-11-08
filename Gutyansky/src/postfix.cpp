#include "postfix.h"

#include <unordered_set>
#include <memory>
#include <cstring>
#include "stack.h"
#include "dummy_provider.h"
#include "postfix_member.h"
#include "postfix_add.h"
#include "postfix_sub.h"
#include "postfix_div.h"
#include "postfix_mult.h"
#include "postfix_number.h"
#include "postfix_var.h"
#include "postfix_uminus.h"
#include "postfix_sin.h"
#include "postfix_cos.h"
#include "postfix_exp.h"

using Lexer::Token;
using Lexer::TokenType;

struct TokenTypePairHasher
{
    size_t operator()(std::pair<TokenType, TokenType> t) const
    {
        return static_cast<size_t>(t.first) * 1000 + static_cast<size_t>(t.second);
    }
};

static const std::unordered_set<std::pair<TokenType, TokenType>, TokenTypePairHasher> validTokenSequences{
    {TokenType::NONE, TokenType::NUM},
    {TokenType::NONE, TokenType::ID},
    {TokenType::NONE, TokenType::LPAR},
    {TokenType::NONE, TokenType::MINUS},
    {TokenType::NONE, TokenType::ENDOFFILE},
    {TokenType::NUM, TokenType::PLUS},
    {TokenType::NUM, TokenType::MINUS},
    {TokenType::NUM, TokenType::MULT},
    {TokenType::NUM, TokenType::DIV},
    {TokenType::NUM, TokenType::RPAR},
    {TokenType::NUM, TokenType::ENDOFFILE},
    {TokenType::ID, TokenType::PLUS},
    {TokenType::ID, TokenType::MINUS},
    {TokenType::ID, TokenType::MULT},
    {TokenType::ID, TokenType::DIV},
    {TokenType::ID, TokenType::LPAR},
    {TokenType::ID, TokenType::RPAR},
    {TokenType::ID, TokenType::ENDOFFILE},
    {TokenType::LPAR, TokenType::NUM},
    {TokenType::LPAR, TokenType::ID},
    {TokenType::LPAR, TokenType::LPAR},
    {TokenType::LPAR, TokenType::MINUS},
    {TokenType::RPAR, TokenType::RPAR},
    {TokenType::RPAR, TokenType::PLUS},
    {TokenType::RPAR, TokenType::MINUS},
    {TokenType::RPAR, TokenType::MULT},
    {TokenType::RPAR, TokenType::DIV},
    {TokenType::RPAR, TokenType::ENDOFFILE},
    {TokenType::PLUS, TokenType::NUM},
    {TokenType::PLUS, TokenType::ID},
    {TokenType::PLUS, TokenType::LPAR},
    {TokenType::MINUS, TokenType::NUM},
    {TokenType::MINUS, TokenType::ID},
    {TokenType::MINUS, TokenType::LPAR},
    {TokenType::MULT, TokenType::NUM},
    {TokenType::MULT, TokenType::ID},
    {TokenType::MULT, TokenType::LPAR},
    {TokenType::DIV, TokenType::NUM},
    {TokenType::DIV, TokenType::ID},
    {TokenType::DIV, TokenType::LPAR},
};

bool ValidateToken(TokenType prev, TokenType cur)
{
    return validTokenSequences.count({ prev, cur }) > 0;
}

bool IsBinaryOperator(Token token)
{
    switch (token.Type())
    {
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::MULT:
    case TokenType::DIV:
        return true;
    default:
        return false;
    }
}

bool IsUnaryOperator(Token token)
{
    switch (token.Type())
    {
    case TokenType::MINUS:
        return true;
    case TokenType::ID:
        return token.Value() == "sin" || token.Value() == "cos" || token.Value() == "exp";
    default:
        return false;
    }
}

PostfixMember ToMember(Token token, bool unary = false)
{
    switch (token.Type())
    {
    case TokenType::PLUS: return PostfixMember(token, 1);
    case TokenType::MINUS: return PostfixMember(token, 1, unary);
    case TokenType::MULT: return PostfixMember(token, 2);
    case TokenType::DIV: return PostfixMember(token, 2);
    case TokenType::LPAR: return PostfixMember(token);
    default: throw std::invalid_argument(__FUNCTION__ ": Unknown operation provided");
    }
}

std::shared_ptr<IPostfixOperation> CreateOperation(Token token, bool unary = false)
{
    switch (token.Type())
    {
    case TokenType::NUM:
        return std::make_shared<PostfixNumber>(std::stod(token.Value()));
    case TokenType::ID:
        if (unary)
        {
            if (token.Value() == "sin") return std::make_shared<PostfixSin>();
            else if (token.Value() == "cos") return std::make_shared<PostfixCos>();
            else if (token.Value() == "exp") return std::make_shared<PostfixExp>();
            else throw std::runtime_error(__FUNCTION__ ": Unknown function");
        } else
        {
            return std::make_shared<PostfixVar>(token.Value());
        }
    case TokenType::PLUS:
        return std::make_shared<PostfixAdd>();
    case TokenType::MINUS:
        if (unary)
            return std::make_shared<PostfixUMinus>();
        else
            return std::make_shared<PostfixSub>();
    case TokenType::MULT:
        return std::make_shared<PostfixMult>();
    case TokenType::DIV:
        return std::make_shared<PostfixDiv>();
    default:
        throw std::runtime_error(__FUNCTION__ ": Invalid operation");
    }
}

void Postfix::GeneratePostfix()
{
    if (m_GeneratedPostfix) return;

    m_Postfix.clear();

    Stack<PostfixMember> tokens;
    int parentheses = 0;

    Token prev = Token(TokenType::NONE);
    Token tok = prev;

    do
    {
        prev = tok;
        tok = m_Lexer.NextToken();

        TokenType prevType = prev.Type();
        TokenType curType = tok.Type();

        if (!ValidateToken(prevType, curType)) throw std::runtime_error(__FUNCTION__ ": Unexpected token");

        if (curType == TokenType::LPAR) parentheses++;
        if (curType == TokenType::RPAR) parentheses--;
        if (parentheses < 0) throw std::runtime_error(__FUNCTION__ ": Unexpected right parenthesis");

        if (curType == TokenType::LPAR)
        {
            tokens.Push(ToMember(tok));
        } else if (curType == TokenType::RPAR)
        {
            while (tokens.Top().Type() != TokenType::LPAR)
            {
                m_Postfix.push_back(CreateOperation(tokens.Top().Token()));
                tokens.Pop();
            }
            tokens.Pop();

            while (tokens.Size() && tokens.Top().IsUnary())
            {
                m_Postfix.push_back(CreateOperation(tokens.Top().Token(), true));
                tokens.Pop();
            }
        } else if (IsUnaryOperator(tok) && (prevType == TokenType::NONE || prevType == TokenType::LPAR || IsBinaryOperator(prev)))
        {
            tokens.Push(PostfixMember(tok, 0, true));
        } else if (IsBinaryOperator(tok))
        {
            PostfixMember member = ToMember(tok);
            while (tokens.Size() && member.Precedence() <= tokens.Top().Precedence())
            {
                m_Postfix.push_back(CreateOperation(tokens.Top().Token()));
                tokens.Pop();
            }
            tokens.Push(member);
        } else if (curType == TokenType::NUM || curType == TokenType::ID)
        {
            m_Postfix.push_back(CreateOperation(tok));

            while (tokens.Size() && tokens.Top().IsUnary())
            {
                m_Postfix.push_back(CreateOperation(tokens.Top().Token(), true));
                tokens.Pop();
            }
        }

    } while (tok.Type() != TokenType::ENDOFFILE);

    if (parentheses != 0)
    {
        throw std::runtime_error(__FUNCTION__ ": Unclosed parenthesis");
    }

    while (tokens.Size())
    {
        m_Postfix.push_back(CreateOperation(tokens.Top().Token(), tokens.Top().IsUnary()));
        tokens.Pop();
    }

    m_GeneratedPostfix = true;
}

double Postfix::Calculate(const std::shared_ptr<IVariableProvider>& variables)
{
    auto postfix = GetPostfix();

    double a = 0.0, b = 0.0;

    ExecutionContext ctx(variables);

    for (auto op : postfix)
    {
        op->Execute(ctx);
    }

    return ctx.Result();
}

double Postfix::Calculate()
{
    return Calculate(std::make_shared<DummyProvider>());
}
