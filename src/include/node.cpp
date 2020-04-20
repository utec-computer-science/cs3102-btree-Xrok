template <typename T, int ORDER>
struct BNode
{
    int count;
    T data[ORDER + 1];
    BNode *children[ORDER + 2];

    BNode()
    {
        count = 0;
        for (int i = 0; i < ORDER; i++)
        {
            children[i] = NULL;
        }
    }

    void insert(int pos, const T &value)
    {
        int j = count;
        while (j > pos)
        {
            data[j] = data[j - 1];
            children[j + 1] = children[j];
            j--;
        }
        data[j] = value;
        children[j + 1] = children[j];
        count++;
    }

    bool is_overflow() { return count > ORDER; }
};
