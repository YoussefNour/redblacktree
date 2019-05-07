/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: user
 *
 * Created on 09 May 2018, 01:06
 */ 
#include<iostream>
#include<cstdio>
 
using namespace std;

struct contact
{
    int n;
    string name;
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
      void insert(int n ,string name);
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void del(int n);
      node* successor(node *);
      void delfix(node *);
      void disp();
      void display( node *);
      node* search(int x);
};
void RBtree::insert(int x,string name)
{
     node *p,*q;
     node *t=new node;
     t->key.n=x;
     t->key.name=name;
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
              if(p->key.n<t->key.n)
                  p=p->right;
              else
                  p=p->left;
         }
         t->parent=q;
         if(q->key.n<t->key.n)
              q->right=t;
         else
              q->left=t;
     }
     insertfix(t);
}
void RBtree::insertfix(node *t)
{
     node *u;
     if(root==t)
     {
         t->color='b';
         return;
     }
     while(t->parent!=NULL&&t->parent->color=='r')
     {
           node *g=t->parent->parent;
           if(g->left==t->parent)
           {
                        if(g->right!=NULL)
                        {
                              u=g->right;
                              if(u->color=='r')
                              {
                                   t->parent->color='b';
                                   u->color='b';
                                   g->color='r';
                                   t=g;
                              }
                        }
                        else
                        {
                            if(t->parent->right==t)
                            {
                                 t=t->parent;
                                 leftrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            rightrotate(g);
                        }
           }
           else
           {
                        if(g->left!=NULL)
                        {
                             u=g->left;
                             if(u->color=='r')
                             {
                                  t->parent->color='b';
                                  u->color='b';
                                  g->color='r';
                                  t=g;
                             }
                        }
                        else
                        {
                            if(t->parent->left==t)
                            {
                                   t=t->parent;
                                   rightrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            leftrotate(g);
                        }
           }
           root->color='b';
     }
}
 
void RBtree::del(int n)
{
     node *p;
     p=root;
     node *y=NULL;
     node *q=NULL;
     int found=0;
     while(p!=NULL&&found==0)
     {
           if(p->key.n==n)
               found=1;
           if(found==0)
           {
                 if(p->key.n<n) p=p->right;
                 else
                    p=p->left;
           }
     }
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
             p->key.n=y->key.n;
         }
         if(y->color=='b')
             delfix(q);     
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
 
void RBtree::disp()
{
     display(root);
}
void RBtree::display(node *p)
{
     if(p!=NULL)
     {
                cout<<"\n\t NODE: ";
                cout<<"\n number: "<<p->key.n;
                cout<<"\n Colour: "; if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red"; if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->key.n;
                else
                       cout<<"\n There is no parent of the node. "; if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->key.n;
                else
                       cout<<"\n There is no right child of the node. "; if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->key.n;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl; if(p->left)
    {
                 cout<<"\n\nLeft:\n"; display(p->left);
    }
    /*else
     cout<<"\nNo Left Child.\n";*/ if(p->right)
    {
     cout<<"\n\nRight:\n"; display(p->right);
    }
    /*else
     cout<<"\nNo Right Child.\n"*/
     }
}
node* RBtree::search(int n)
{
     if(root==NULL)
     {
           cout<<"\nEmpty Tree\n" ;
           return  NULL;
     }
     node *p=root;
     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->key.n==n)
                found=1;
            if(found==0)
            {
                 if(p->key.n<n) p=p->right;
                 else
                      p=p->left;
            }
     }
     if(found==0)
          cout<<"\nElement Not Found.";
     else
     {
                cout<<"\n\t FOUND NODE: ";
                cout<<"\n number: "<<p->key.name;
                cout<<"\n number: "<<p->key.n;
                cout<<"\n Colour: "; if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red"; if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->key.n;
                else
                       cout<<"\n There is no parent of the node. "; if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->key.n;
                else
                       cout<<"\n There is no right child of the node. "; if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->key.n;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;
 
     }
}
    int main()
{
    int testCC, instType,Num;
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
                contacts.insert(Num,name);
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
                    std::cout<<p->key.name<<std::endl;
                else
                    std::cout<<searchQuery<<std::endl;
        }
    }
    return 0;
}

 

