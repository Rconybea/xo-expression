/* @file Variable.cpp */

#include "Variable.hpp"
#include "Environment.hpp"

namespace xo {
    namespace ast {
        void
        Variable::attach_envs(ref::brw<Environment> e) {
            /** e makes accessible all enclosing lexical scopes **/
            this->path_ = e->lookup_binding(this->name_);
        } /*attach_envs*/

        void
        Variable::display(std::ostream & os) const {
            os << "<Variable"
               << xtag("name", name_)
               << xtag("type", this->valuetype()->short_name())
               << ">";
        } /*display*/
    } /*namespace ast*/
} /*namespace xo*/


/* end Variable.cpp */
