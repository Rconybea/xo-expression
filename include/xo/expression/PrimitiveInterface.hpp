/** @file PrimitiveInterface.hpp
 *
 *  Author: Roland Conybeare
 **/

#pragma once

#include "FunctionInterface.hpp"
#include "llvmintrinsic.hpp"

//#include <cstdint>

#include <type_traits>
namespace xo {
    namespace ast {
        class PrimitiveInterface : public FunctionInterface {
        public:
            using void_function_type = void (*)();

        public:
            PrimitiveInterface(TypeDescr fn_type)
                : FunctionInterface(exprtype::primitive, fn_type) {}

            /** downcast from Expression **/
            static ref::brw<PrimitiveInterface> from(ref::brw<Expression> x) {
                return ref::brw<PrimitiveInterface>::from(x);
            }

            /** if true,  Jit will try to explicitly symbol for this primitive
             *  (instead of looking it up in host process).
             *  Don't know if this works.
             *  Do know it's not needed for ::sin(), ::sqrt().
             *  Do know that my extern "C" functions like ::mul_i32(), ::mul_f64()
             *  need something else.
             **/
            virtual bool explicit_symbol_def() const = 0;

            /** function address for this primitive **/
            virtual void_function_type function_address() const = 0;

            /** get llvm intrinsic hint for this primitive **/
            virtual llvmintrinsic intrinsic() const = 0;

            // virtual const std::string & name() const;
            // virtual int n_arg() const;
            // virtual TypeDescr fn_retval() const;
            // virtual TypeDescr fn_arg(uint32_t i) const;

        private:
        }; /*PrimitiveInterface*/
    } /*namespace ast*/
} /*namespace xo*/


/** end PrimitiveInterface.hpp **/
