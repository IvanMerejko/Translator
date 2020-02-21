//
// Created by Ivan on 19.02.2020.
//

#include "Tree.h"
#include "../Context.h"
#include "../Common/TypesFmd.h"
#include "../Common/Utils.h"
void Tree::Print(NodePtr& node, int count) const
{
	if (node)
	{
		utils::PrintSeparator(count);
		std::cout << std::get<0>(node->m_token) << " "
			<< std::get<1>(node->m_token) << "\n";
		Print(node->m_child, count + 3);
		Print(node->m_next, count);
	}

}