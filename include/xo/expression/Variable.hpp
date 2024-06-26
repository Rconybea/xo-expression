/** @file Variable.hpp
 *
 *  Author: Roland Conybeare
 **/

#pragma once

#include "Expression.hpp"

namespace xo {
    namespace ast {

        /** @class Variable
         *  @brief syntax for a variable reference
         **/
        class Variable : public Expression {
        public:
            /** create expression representing a variable
             *  identified by @p name,  that can take on values
             *  described by @p var_type.
             **/
            static ref::rp<Variable> make(const std::string & name,
                                          TypeDescr var_type) {
                return new Variable(name, var_type);
            }

            /** downcast from Expression **/
            static ref::brw<Variable> from(ref::brw<Expression> x) {
                return ref::brw<Variable>::from(x);
            }

            const std::string & name() const { return name_; }

            virtual std::set<std::string> get_free_variables() const override {
                std::set<std::string> retval;
                retval.insert(this->name_);
                return retval;
            }

            virtual std::size_t visit_preorder(VisitFn visitor_fn) override {
                visitor_fn(this);
                return 1;
            }

            virtual void attach_envs(ref::brw<Environment> /*p*/) override {}

#ifdef NOT_USING
            virtual std::int32_t find_free_vars(std::set<ref::brw<Variable>> * p_set) override {
            }
#endif

            virtual void display(std::ostream & os) const override;

        private:
            Variable(const std::string & name,
                     TypeDescr var_type)
                : Expression(exprtype::variable, var_type),
                  name_{name} {}

        private:
            /** variable name **/
            std::string name_;
        }; /*Variable*/

        inline ref::rp<Variable>
        make_var(const std::string & name,
                 reflect::TypeDescr var_type) {
            return Variable::make(name, var_type);
        }
    } /*namespace ast*/
} /*namespace xo*/


/** end Variable.hpp **/
