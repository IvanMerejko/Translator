#pragma once

#include <memory>
#include "../Common/TypesFmd.h"

struct Node;
using NodePtr = std::shared_ptr<Node>;
enum class NodeType
{
	Child,
	Next
};

struct Node
{
    Node() = default;
    Node(std::optional<Address> address)
        : m_address{std::move(address)}
    {};
    std::optional<Address> m_address;
    TokenInfo m_token;
    NodePtr m_child;
    NodePtr m_next;
};


struct Tree
{
    NodePtr m_root;
	void Print(NodePtr& node, int count) const;
};
