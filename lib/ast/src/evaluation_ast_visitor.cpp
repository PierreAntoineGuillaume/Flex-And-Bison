#include "evaluation_ast_visitor.h"

template <>
int v1::ast::fb31::evaluation_ast_visitor<int>::visit(v1::ast::fb31::dual_ast<int> & ast)
{
    switch (ast.symbol)
    {
        case '+': return (ast.left().accept(*this) + ast.right().accept(*this));
        case '-': return (ast.left().accept(*this) - ast.right().accept(*this));
        case '*': return (ast.left().accept(*this) * ast.right().accept(*this));
        case '%':
        case '/':
        {
            const auto & divider = ast.right().accept(*this);
            if (divider == 0)
            {
                throw std::runtime_error("zero division");
            }
            if (ast.symbol == '/')
            {
                return (ast.left().accept(*this) / divider);
            }
            return (ast.left().accept(*this) % divider);
        }
        default:throw std::runtime_error(unknown_symbol + ast.symbol );
    }
}
