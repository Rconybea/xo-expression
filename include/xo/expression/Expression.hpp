/** @file Expression.hpp
 *
 *  Author: Roland Conybeare
 **/

#pragma once

#include "xo/reflect/TypeDescr.hpp"
#include "xo/refcnt/Refcounted.hpp"
#include "exprtype.hpp"
#include <functional>

namespace xo {
    namespace ast {
        /** @class Expression
         *  @brief abstract syntax tree for an EGAD program
         *
         *  (Expression Graph with Automagic Derivation)
         *
         *  Things you can do with an Expression:
         *  - evaluate it using an interpreter
         *  - execute it on a VM
         *  - compile using LLVM
         *    see xo-jit/
         *
         *  Expressions are immutable.  This means they can resused
         *  across jit interactions
         *
         *  Every expression evaluates to a value with a particular type
         **/
        class Expression : public ref::Refcount {
        public:
            using VisitFn = std::function<void (ref::brw<Expression>)>;
            using TypeDescr = xo::reflect::TypeDescr;

        public:
            explicit Expression(exprtype extype, TypeDescr valuetype)
                : extype_{extype}, valuetype_{valuetype}{}

            exprtype extype() const { return extype_; }
            TypeDescr valuetype() const { return valuetype_; }

            /** visit each Expression node in this AST,
             *  and invoke @p fn for each.
             *  Returns the number of nodes visited.
             *  Preorder: call @p fn for a node before visiting children
             **/
            virtual std::size_t visit_preorder(VisitFn visitor_fn) = 0;

            /** write human-readable representation to stream **/
            virtual void display(std::ostream & os) const = 0;
            /** human-readable string representation **/
            virtual std::string display_string() const;

        private:
            /** expression type (constant | apply | ..) for this expression **/
            exprtype extype_ = exprtype::invalid;
            /** type information (when available) for values produced by this
             *  expression.
             **/
            TypeDescr valuetype_ = nullptr;
        }; /*Expression*/

        inline std::ostream &
        operator<<(std::ostream & os, const Expression & x) {
            x.display(os);
            return os;
        }
    } /*namespace ast*/
} /*namespace xo*/

/** end Expression.hpp **/
