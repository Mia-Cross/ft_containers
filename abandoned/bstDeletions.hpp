
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