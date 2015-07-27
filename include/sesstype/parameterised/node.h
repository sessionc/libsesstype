/**
 * \file sesstype/parameterised/node.h
 * \brief Statements in a protocol or session (parameterised).
 */
#ifndef SESSTYPE__PARAMETERISED__NODE_H__
#define SESSTYPE__PARAMETERISED__NODE_H__

#include "sesstype/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#define  ST_NODE_FOR       101
#define  ST_NODE_ALLREDUCE 102
#define  ST_NODE_ONEOF     103
#define  ST_NODE_IF        104

#ifdef __cplusplus
// Load base classes from non-parameterised sesstypes to current namespace.

using sesstype::Node;
using sesstype::BlockNode;

#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE_H__
