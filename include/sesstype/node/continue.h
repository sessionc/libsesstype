#ifndef SESSTYPE__NODE__CONTINUE_H__
#define SESSTYPE__NODE__CONTINUE_H__

#ifdef __cplusplus
#include <string>
#endif

#include "sesstype/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace util {

class NodeVisitor;

} // namespace util
} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Continue statements.
 */
class ContinueNode : public Node {
  public:
    /// \brief ContinueNode constructor.
    /// \param[in] label of Choice Node.
    ContinueNode(std::string label);

    /// \brief ContinueNode copy constructor.
    ContinueNode(const ContinueNode &node);

    /// \brief ContinueNode destructor.
    ~ContinueNode() override;

    /// \brief clone a ContinueNode.
    ContinueNode *clone() const override;

    /// \brief Repalce label of ContinueNode.
    /// \param[in] label of ContinueNode to replace with.
    void set_label(std::string label);

    /// \returns label of ContinueNode.
    std::string label() const;

    void accept(util::NodeVisitor &v) override;

  private:
    std::string label_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_continue_node(char *label);
st_node *st_continue_node_set_label(st_node *node, char *label);
const char *st_continue_node_get_label(st_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namspace sesstype
#endif

#endif//SESSTYPE__NODE__CONTINUE_H__
