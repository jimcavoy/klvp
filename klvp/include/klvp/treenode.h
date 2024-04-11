#pragma once

namespace lcss
{
	template< class N >
	class TreeNode
	{
	public:
		typedef TreeNode* TreeNodePtr;
	public:
		TreeNode()
			:parent_(nullptr)
			, child_(nullptr)
			, sibling_(nullptr)
		{}

		~TreeNode() {
		}

		N getData() { return data_; }

		void setData(N data)
		{
			data_ = data;
		}

		TreeNodePtr parent() { return parent_; }
		TreeNodePtr child() { return child_; }
		TreeNodePtr sibling() { return sibling_; }

		void setParent(TreeNodePtr p)
		{
			parent_ = p;
		}

		void setSibling(TreeNodePtr s)
		{
			sibling_ = s;
		}

		void setChild(TreeNodePtr c)
		{
			child_ = c;
		}

		void addChild(TreeNodePtr c)
		{
			if (child_ == nullptr)
			{
				child_ = c;
				c->setParent(this);
			}
			else
			{
				TreeNodePtr last = child_;
				while (last->sibling() != nullptr)
					last = last->sibling();
				last->setSibling(c);
				c->setParent(this);
			}
		}

		void removeChild(TreeNodePtr c)
		{
			if (c == nullptr)
				return;

			if (c == child_)
			{
				child_ = c->sibling();
				return;
			}

			TreeNodePtr s = findPrevSibling(c);

			if (s != nullptr)
				s->setSibling(c->sibling());
		}

	private:

		TreeNodePtr findPrevSibling(TreeNodePtr s)
		{
			TreeNodePtr n = s->parent()->child(); // get the first sibling

			while (n != nullptr)
			{
				if (n->sibling() == s)
					return n;
				n = n->sibling(); // get the next sibling
			}
			return n;
		}

	private:
		N data_;
		TreeNodePtr parent_;
		TreeNodePtr child_;
		TreeNodePtr sibling_;
	};

	template< class T, class P >
	void preorderTreeWalk(T node, P p)
	{
		if (node != nullptr)
		{
			p(node);
			preorderTreeWalk(node->child(), p);
			preorderTreeWalk(node->sibling(), p);
		}
	}

	template< class T, class P >
	void postorderTreeWalk(T node, P p)
	{
		if (node != nullptr)
		{
			postorderTreeWalk(node->child(), p);
			postorderTreeWalk(node->sibling(), p);
			p(node);
		}
	}
}