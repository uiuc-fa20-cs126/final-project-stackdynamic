#include "core/parser.h"
#include "core/exception.h"

namespace ogol::core {

Parser::Parser(queue<Token> &tokens) : tokens_(tokens) {}

SExpr Parser::parse() {
  vector<SExpr> parsed;
  Token token = tokens_.front();
  tokens_.pop();
  if (token.value != "(") {
    throw ParseError(
        "Attempted to parse start of S-expression, but no such element found.",
        token.line_num);
  }
  while (token.value != ")") {
    if (tokens_.empty()) {
      throw ParseError("Unexpected EOF: unbalanced parenthetical.",
                       token.line_num);
    }
    token = tokens_.front();
    tokens_.pop();
    if (token.value == "(") {
      parsed.push_back(parse());
    } else {
      parsed.emplace_back(Atom(token));
    }
  }
  return SExpr(parsed);
}

} // namespace ogol::core