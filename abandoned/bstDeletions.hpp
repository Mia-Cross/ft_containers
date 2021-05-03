        // create new element with only a key
        binTree(const Key key, binTree *root) : _root(root), _left(NULL), _right(NULL),
            _comp(Compare()), _allocBT(Alloc())
        {
            // std::cout << "Key Constructor called -> " << this << " ~ key=" << key << std::endl;
            _pair = _allocBT.allocate(1);
            _allocBT.construct(_pair, pair_t(key, 0));
            if (!_root)
                _root = this;
        }

// original version

        void replaceInParent(binTree *newChild) {
            binTree *parent = this->getParent();
            if (parent)
            {
                if (this == parent->_left)
                    parent->_left = newChild;
                else
                    parent->_right = newChild;
            }
        }

        void deleteFromTree(const Key &to_del) {
            if (_comp(to_del, this->getKey()))
            {
                this->_left->deleteFromTree(to_del);
                return;
            }
            if (_comp(this->getKey(), to_del))
            {
                this->_right->deleteFromTree(to_del);
                return;
            }
            // Delete the key here
            if (this->_left && this->_right)  // If both children are present
            {
                binTree *successor = getMostLeft(this->_right);
                // pair_t newContent(successor->getKey(), this->_pair->second);
                *this = *successor;
                // this->getKey() = successor->getKey();
                successor->deleteFromTree(successor->getKey());
            }
            else if (this->_left)  // If the node has only a *_left* child
                this->replaceInParent(this->_left);
            else if (this->_right) // If the node has only a *_right* child
                this->replaceInParent(this->_right);
            else
                this->replaceInParent(NULL);  // This node has no children
            if (this != _root)
                delete this;
        }
size_t      getLevel() const {
            size_t lvl = 0;
            for (binTree *node = root; node && node != this; lvl++)
            {
                if (comp(node->getKey(), this->getKey()))
                    node = node->right;
                else
                    node = node->left;
            }
            // std::cout << "LEVEL RETURNED = " << lvl << std::endl;
            return (lvl);
        }

insert iteratif :
    std::pair<binTree*,bool> insert(const Key &key, T &val) {
if (!root)
{
    allocBT.construct(this->value, pair_t(key, val));
    root = this;
    return (std::pair<binTree*,bool>(root, true));
}
binTree *node = getNode(key, root);
// std::cout << "node = " << node << std::endl;
if (!node)
{
    node = new binTree(key, val, root);
    setChildInParent(node, key);
    // std::cout << "root du new elemnt = " << node->root << std::endl;
    return (std::pair<binTree*,bool>(node, true));
}
if (key == node->getKey())
{
    node->value->second = val;
    return (std::pair<binTree*,bool>(node, false));
}
}

        void setChildInParent(binTree *child, const Key &key) {
 if (comp(parent->getKey(), key))
            {
                if (parent->right)
                    setChildInParent(parent->right, child, key);
                parent->right = child;
            }
            else if (comp(key, parent->getKey()))
            {
                if (parent->left)
                    setChildInParent(parent->left, child, key);
                parent->left = child;
            }
            }

        binTree     *getNextIter(size_t prevLevel) const {
            if (!(right && left) || prevLevel > this->getLevel())
            {
                binTree *next = this->getParent();
                while (comp(this->getKey(), next->getKey()))
                    next = next->getParent();
                return (next);
            }
            if (right)
            {
                std::cout << " hm " << std::endl;
                return (right->getMostLeft(right));
            }
            else
                return (NULL);
                return (this->getParent());
            if (prevLvl > this->getLevel())
            {
                if (comp(this->getKey(), this->getParent()->getKey()))
                    return (this->getParent());
                else
                    return (this->getRight()->getMostLeft());
            }
            else
            {
                if (comp(this->getKey(), this->getParent()->getKey()))
                    return (this->getParent());
                else
                    return (this->getRight()->getMostLeft());
            }
            else if comp(node->getParent()->getKey(), node->getKey()) && prevLvl < level)
            size_t lvl = this->getLevel();
            if (!lvl)
                return (this->right);
            binTree *parent = this->getParent();
            if (this->right)
                return (this->right);
            if (comp(this->getKey(), parent->getKey()))
                return (parent);
            else
                return (parent->right)
            else if (this->right)
                return (this->right);
            else
                return (NULL);
        }

void        setValue(T &val) { allocBT.construct(this->value, val); }
void        setValue(pair_t value) { allocBT.construct(this->value, value); }
void        setRootSingle(binTree *newRoot) { this->root = newRoot; }
void        setRootAll(binTree *newRoot) {
    binTree *elem = getMostLeft();
    while (elem != getMostRight())
        elem->root = newRoot;
    elem->root = newRoot;
}
binTree                 *getMostLeft() const {
    binTree *mostLeft = root;
    while (mostLeft && mostLeft->left)
        mostLeft = mostLeft->left;
    return (mostLeft);
}
binTree                 *getMostRight() const {
    binTree *mostRight = root;
    while (mostRight && mostRight->right != NULL)
        mostRight = mostRight->right;
    return (mostRight);
}
binTree  *getNode(const Key &to_find, binTree *node) const {
    binTree *elem = root;
    while (elem->value->first != to_find)
    {
        if (comp(elem->value->first, to_find))
        {
            if (!elem->right)
                break;
            elem = elem->right;
        }
        else
        {
            if (!elem->left)
                break;
            elem = elem->left;
        }
    }
    return (elem);}

void insert(binTree *to_add) {
    to_add->root = this->root;
    binTree *elem = this->root;
    while (elem != to_add)
    {
        if (this->comp(elem->value->first, to_add->value->first))
        {
            if (!elem->right)
            {
                elem->right = to_add;
                // to_add->prev = elem;
            }
            elem = elem->right;
        }
        else
        {
            if (!elem->left)
            {
                elem->left = to_add;
                // to_add->prev = elem;
            }
            elem = elem->left;
        }
    }
}
    
        std::cout << "this->left\t" << this->left << std::endl;
        std::cout << "this->prev\t" << this->prev << std::endl;
        std::cout << "this->left->prev\t" << this->left->prev << std::endl;

void extractElement() {
    binTree *candidate;
    if (this->right->left)
    {
        candidate = this->right->left;
        while (candidate->left)
            candidate = candidate->left;
    }
    else
    {
        candidate = this->left->right;
        while (candidate->right)
            candidate = candidate->right;
    }
    candidate->right = this->right;
    candidate->left = this->left;
    // this->left->prev = candidate;
    // this->right->prev = candidate;
    if (this == root)
        setRootAll(candidate);
}

void extractElement(binTree *child) {
    // child->prev = this->prev;
    binTree *parent = this->getParent();
    if (parent && parent->right == this)
        parent->right = child;
    else if (parent && parent->left == this)
        parent->left = child;
    if (this == root)
        child->root = child;
}

void deleteElement() {
    if (this->left && !this->right)
        this->extractElement(this->left);
    else if (this->right && !this->left)
        this->extractElement(this->right);
    else if (this->right && this->left)
        this->extractElement();
    else
    {
        binTree *parent = this->getParent();
        if (parent && this == parent->right)
            parent->right = NULL;
        else if (parent && this == parent->left)
            parent->left = NULL;
    }
    std::cout << "deleting this ->\t" << this << std::endl;
    delete this;
}