#ifndef ST_NORMALISE__H__
#define ST_NORMALISE__H__
/**
 * \file
 * This file contains the canonicalisation functions of (multiparty) session
 * type nodes (st_node).
 *
 */

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief Normalise the node obtained by protocol-parsing or code-parsing.
 * 
 * @param[in,out] node Node to normalise.
 *
 * \returns Normalise node.
 */
st_node *st_node_normalise(st_node *node);


/**
 * \brief Refactor the node obtained by code-parsing.
 *
 * @param[in,out] node Node to refactor.
 *
 * \returns Refactored node.
 */
st_node *st_node_refactor(st_node *node);


#ifdef __cplusplus
}
#endif

#endif // ST_NORMALISE__H__
