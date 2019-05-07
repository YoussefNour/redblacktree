#include <iostream>

struct contact
{
    std::string contactName;
    int contactNumber;
};

struct node
{
    contact key;
    node *parent;
    char color;
    node *left;
    node *right;
};
class RBtree
{
    node *root;
    node *q;
public :
    RBtree()
    {
        q=NULL;
        root=NULL;
    }
    void insert(int contactNumber, std::string contactName);
    void insertfix(node *);
    void leftrotate(node *);
    void rightrotate(node *);
    void del(int query);
    node* successor(node *);
    void delfix(node *);
    node* search(int query);
};
void RBtree::insert(int contactNumber, std::string contactName)
{
    node *p,*q;
    node *t=new node;
    t->key.contactNumber = contactNumber;
    t->key.contactName = contactName;
    t->left=NULL;
    t->right=NULL;
    t->color='r';
    p=root;
    q=NULL;
    if(root==NULL)
    {
        root=t;
        t->parent=NULL;
    }
    else
    {
        while(p!=NULL)
        {
            q=p;
            if(p->key.contactNumber<t->key.contactNumber)
                p=p->right;
            else
                p=p->left;
        }
        t->parent=q;
        if(q->key.contactNumber<t->key.contactNumber)
            q->right=t;
        else
            q->left=t;
    }
    insertfix(t);
}
void RBtree::insertfix(node *z)
{
    if (z->parent != NULL && z->parent->parent != NULL)
    {
        while (z != NULL && z->parent != NULL &&
               z->parent->parent != NULL && !z->parent->color == 'b')
        {
            if (z->parent == z->parent->parent->left)
            {
                node *y = z->parent->parent->right;
                if (y != NULL && y->color == 'r')
                {
                    z->parent->color = 'b';
                    y->color = 'b';
                    z->parent->parent->color = 'r';
                    z = z->parent->parent;
                }
                else if (z == z->parent->right)
                {
                    z = z->parent;
                    leftrotate(z);
                }
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                rightrotate(z->parent->parent);

            }
            else
            {

                node *y = z->parent->parent->left;
                if (y != NULL && y->color == 'r')
                {
                    z->parent->color = 'b';
                    y->color = 'b';
                    z->parent->parent->color = 'r';
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left) 
                    {
                        z = z->parent;
                        rightrotate(z);
                    }
                    z->parent->color = 'b'; 
                    z->parent->parent->color = 'r'; 
                    leftrotate(z->parent->parent);
                }
            }
        }
    }
}
void RBtree::del(int query)
{
    if(root==NULL)
        return ;

    node *p;
    p=root;
    node *y=NULL;
    node *q=NULL;
    int found=0;
    while(p!=NULL&&found==0)
    {
        if(p->key.contactNumber==query)
            found=1;
        if(found==0)
        {
            if(p->key.contactNumber<query)
                p=p->right;
            else
                p=p->left;
        }
    }
    if(found==0)
        return ;
    else
    {
        if(p->left==NULL||p->right==NULL)
            y=p;
        else
            y=successor(p);
        if(y->left!=NULL)
            q=y->left;
        else
        {
            if(y->right!=NULL)
                q=y->right;
            else
                q=NULL;
        }
        if(q!=NULL)
            q->parent=y->parent;
        if(y->parent==NULL)
            root=q;
        else
        {
            if(y==y->parent->left)
                y->parent->left=q;
            else
                y->parent->right=q;
        }
        if(y!=p)
        {
            p->color=y->color;
            p->key=y->key;
        }
        if(y->color=='b')
            delfix(q);
    }
}

void RBtree::delfix(node *p)
{
    node *s;
    while(p!=root&&p->color=='b')
    {
        if(p->parent->left==p)
        {
            s=p->parent->right;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                leftrotate(p->parent);
                s=p->parent->right;
            }
            if(s->right->color=='b'&&s->left->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->right->color=='b')
                {
                    s->left->color=='b';
                    s->color='r';
                    rightrotate(s);
                    s=p->parent->right;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->right->color='b';
                leftrotate(p->parent);
                p=root;
            }
        }
        else
        {
            s=p->parent->left;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                rightrotate(p->parent);
                s=p->parent->left;
            }
            if(s->left->color=='b'&&s->right->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->left->color=='b')
                {
                    s->right->color='b';
                    s->color='r';
                    leftrotate(s);
                    s=p->parent->left;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->left->color='b';
                rightrotate(p->parent);
                p=root;
            }
        }
        p->color='b';
        root->color='b';
    }
}

void RBtree::leftrotate(node *p)
{
    if(p->right==NULL)
        return ;
    else
    {
        node *y=p->right;
        if(y->left!=NULL)
        {
            p->right=y->left;
            y->left->parent=p;
        }
        else
            p->right=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->left=p;
        p->parent=y;
    }
}
void RBtree::rightrotate(node *p)
{
    if(p->left==NULL)
        return ;
    else
    {
        node *y=p->left;
        if(y->right!=NULL)
        {
            p->left=y->right;
            y->right->parent=p;
        }
        else
            p->left=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->right=p;
        p->parent=y;
    }
}

node* RBtree::successor(node *p)
{
    node *y=NULL;
    if(p->left!=NULL)
    {
        y=p->left;
        while(y->right!=NULL)
            y=y->right;
    }
    else
    {
        y=p->right;
        while(y->left!=NULL)
            y=y->left;
    }
    return y;
}

node* RBtree::search(int query)
{
    if(root==NULL)
        return NULL;

    node *p=root;
    int found=0;
    while(p!=NULL&& found==0)
    {
        if(p->key.contactNumber==query)
            found=1;
        if(found==0)
        {
            if(p->key.contactNumber<query) p=p->right;
            else
                p=p->left;
        }
    }
    if(found==1)
        return p;
    return NULL;
}


int main()
{
    int testCC,instType,Num;
    RBtree contacts;
    std::string name;
    std::cin>>testCC;
    for(int i = 0; i<testCC; i++)
    {
        std::cin>>instType;
        switch (instType)
        {
            case 1:
                std::cin>>Num>>name;
                contacts.insert(Num, name);
                break;
            case 2:
                int deleteQuery;
                std::cin>>deleteQuery;
                contacts.del(deleteQuery);
                break;
            case 3:
                int searchQuery;
                std::cin>>searchQuery;
                node* p = contacts.search(searchQuery);
                if(p != NULL)
                    std::cout<<p->key.contactName<<std::endl;
                else
                    std::cout<<searchQuery<<std::endl;
        }
    }
    return 0;
}