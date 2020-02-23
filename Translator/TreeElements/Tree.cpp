//
// Created by Ivan on 19.02.2020.
//

#include "Tree.h"
#include "../Context.h"
#include "../Common/TypesFmd.h"
#include "../Common/Utils.h"

bool isNeedToAdd(const NodePtr& node)
{
	return (!node->m_address && std::get<1>(node->m_token) == 0) ||
		(node->m_child && node->m_child->m_address && node->m_child->m_address == MathFunctionDeclarationE 
			&& node->m_address && node->m_address == DeclarationsE);
}


bool isBlock(const NodePtr& node)
{
	return node->m_address && *node->m_address == BlockE;
}

void Tree::Print(NodePtr& node, int count) const
{
	if (node)
	{
		if (std::get<1>(node->m_token) != 0 || node->m_address)
		{
			utils::PrintSeparator(count);
			if (node->m_address && node->m_address != WriteE)
			{
				count = utils::SpecialPrint(*node->m_address, count, node);
			}
			else
			{

				std::cout << std::get<1>(node->m_token) << " "
					<< std::get<0>(node->m_token) << "\n";
			}
		}


		Print(node->m_child, isNeedToAdd(node) ? count : count + 3);
		Print(node->m_next, isBlock(node) ? count + 3 : count);
	}

}