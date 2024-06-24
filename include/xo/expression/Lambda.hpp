/** @file Lambda.hpp
 *
 *  Author: Roland Conybeare
 **/

#pragma once

#include "Expression.hpp"
#include "FunctionInterface.hpp"
#include "Variable.hpp"
#include <vector>
#include <string>
//#include <cstdint>

namespace xo {
    namespace ast {
        /** @class Lambda
         *  @brief abstract syntax tree for a function definition
         *
         **/
        class Lambda : public FunctionInterface {
        public:
            /**
             *  @p name   Name for this lambda -- must be unique
             *  @p argv   Formal parameters, in left-to-right order
             *  @p body   Expression for body of this function
             **/
            static ref::rp<Lambda> make(const std::string & name,
                                        const std::vector<ref::rp<Variable>> & argv,
                                        const ref::rp<Expression> & body);

            /** downcast from Expression **/
            static ref::brw<Lambda> from(ref::brw<Expression> x) {
                return ref::brw<Lambda>::from(x);
            }

            const std::string & type_str() const { return type_str_; }
            const std::vector<ref::rp<Variable>> & argv() const { return argv_; }
            const ref::rp<Expression> & body() const { return body_; }

            // ----- FunctionInterface -----

            virtual const std::string & name() const override { return name_; }
            /** return number of arguments expected by this function **/
            virtual int n_arg() const override { return argv_.size(); }
            virtual TypeDescr fn_retval() const override { return body_->valuetype(); }
            virtual TypeDescr fn_arg(uint32_t i) const override { return argv_[i]->valuetype(); }

            // ----- Expression -----

            virtual std::size_t visit_preorder(VisitFn visitor_fn) override {
                std::size_t n = 1;

                visitor_fn(this);

                for (const auto & arg : argv_)
                    n += arg->visit_preorder(visitor_fn);

                n += body_->visit_preorder(visitor_fn);

                return n;
            }

            virtual void display(std::ostream & os) const override;

        private:
            /** @param lambda_type.  function type for this lambda.
             *  We arbitrarily choose the form "Retval(*)(Args...)"
             **/
            Lambda(const std::string & name,
                   TypeDescr lambda_type,
                   const std::vector<ref::rp<Variable>> & argv,
                   const ref::rp<Expression> & body);

        private:
            /** lambda name.  Initially supporting only form like
             *    (define (foo x y z)
             *      (+ (* x x) (* y y) (* z z)))
             *
             *  In any case need to supply names for distinct things-for-which-code-is-generated
             *  so that they can be linked etc.
             **/
            std::string name_;
            /** e.g.
             *    "double(double,double)"  for function of two doubles that returns a double
             **/
            std::string type_str_;
            /** formal argument names **/
            std::vector<ref::rp<Variable>> argv_;
            /** function body **/
            ref::rp<Expression> body_;
        }; /*Lambda*/

        inline ref::rp<Lambda>
        make_lambda(const std::string & name,
                    const std::vector<ref::rp<Variable>> & argv,
                    const ref::rp<Expression> & body)
        {
            return Lambda::make(name, argv, body);
        }
    } /*namespace ast*/
} /*namespace xo*/

/** end Lambda.hpp **/
