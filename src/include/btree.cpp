#include "node.cpp"

template <typename T, int ORDER>
class BTree
{
    typedef BNode<T,ORDER> bnode;
    
    enum state
    {
        OVERFLOW,
        UNDERFLOW,
        NORMAL
    };

    bnode *root;

public:
    

    BTree() { root = new bnode; }

    void insert(const T &value)
    {
        int state = insert(root, value);
        if (state == OVERFLOW)
        {
            split_root(root, value);
        }
    }

    int insert(bnode *ptr, const T &value)
    {
        int pos = 0;
        while (pos < ptr->count && ptr->data[pos] < value)
        {
            pos++;
        }
        if (ptr->children[pos] != NULL)
        {
            int state = insert(ptr->children[pos], value);
            if (state == OVERFLOW)
            {
                split(ptr, pos);
            }
        }
        else
        {
            ptr->insert(pos, value);
        }
        return ptr->is_overflow() == true ? OVERFLOW : NORMAL;
    }

    void split(bnode *ptr, int pos)
    {
        bnode *overflow_node = ptr->children[pos]; //OJO
        bnode *left_child = overflow_node;
        bnode *rigth_child = new bnode();

        left_child->count = 0;
        int iter = 0, i;
        for (i = 0; iter < ceil(ORDER / 2.0); i++)
        {
            left_child->children[i] = overflow_node->children[iter];
            left_child->data[i] = overflow_node->data[iter];
            left_child->count++;
            iter++;
        }
        left_child->children[i] = overflow_node->children[iter];
        ptr->insert(pos, overflow_node->data[iter]);
        ptr->children[pos + 1] = rigth_child;

        for (i = 0; iter < ORDER + 1; i++)
        {
            rigth_child->children[i] = overflow_node->children[iter];
            rigth_child->data[i] = overflow_node->data[iter];
            rigth_child->count++;
            iter++;
        }
        rigth_child->children[i] = overflow_node->children[iter];

        ptr->children[pos] = left_child;
        ptr->children[pos + 1] = rigth_child;
    }

    void split_root(bnode *ptr, const T &value)
    {
        bnode *overflow_node = ptr;
        bnode *left_child = new bnode();
        bnode *rigth_child = new bnode();

        int iter = 0, i;
        for (i = 0; iter < ceil(ORDER / 2.0); i++)
        {
            left_child->children[i] = overflow_node->children[iter];
            left_child->data[i] = overflow_node->data[iter];
            left_child->count++;
            iter++;
        }
        left_child->children[i] = overflow_node->children[iter];

        ptr->data[0] = overflow_node->data[iter];
        iter++;

        for (i = 0; iter < ORDER + 1; i++)
        {
            rigth_child->children[i] = overflow_node->children[iter];
            rigth_child->data[i] = overflow_node->data[iter];
            rigth_child->count++;
            iter++;
        }
        rigth_child->children[i] = overflow_node->children[iter];

        ptr->children[0] = left_child;
        ptr->children[1] = rigth_child;
        ptr->count = 1;
    }
    void print()
    {
        print(root, 0);
        std::cout << "________________________\n";
    }

    void print(bnode *ptr, int level)
    {
        if (ptr)
        {
            int i;
            for (i = ptr->count - 1; i >= 0; i--)
            {
                print(ptr->children[i + 1], level + 1);

                for (int k = 0; k < level; k++)
                {
                    std::cout << "    ";
                }
                std::cout << ptr->data[i] << "\n";
            }
            print(ptr->children[i + 1], level + 1);
        }
    }
};