#include <bits/stdc++.h>
using namespace std;

struct Node {
  Node (int data)
    : data (data)
    , left (NULL)
    , right (NULL)
  {}
  int data;
  Node *left;
  Node *right;
};

void levelPrint (Node *root) {
  queue<Node *> q;
  q.push (root);
  q.push (NULL);
  while (!q.empty ()) {
    Node *node = q.front (); q.pop ();
    if (node == NULL) {
      cout << "\n";
      if (!q.empty ()) {
	q.push (NULL);
      }
    }
    else {
      cout << node->data << " ";
      if (node->left != NULL) q.push (node->left);
      if (node->right != NULL) q.push (node->right);
    }
  }
}

pair<int, int> maxSpace (Node *root, int sp = 0) {
  if (root == NULL) return make_pair (sp, sp);
  auto l = maxSpace (root->left, sp - 1);
  auto r = maxSpace (root->right, sp + 1);

  //cout << root->data << " " << l.first << " " << r.second << "\n";
  return make_pair (min (l.first, r.first), max(l.second, r.second));
}

int maxRightSpace (Node *root) {
  return (maxSpace (root, 0).second -1 ) * 2 * 4;
}

int maxLeftSpace (Node *root) {
  return (abs(maxSpace (root, 0).first) -1 ) * 2 * 4;
}

void prettyPrint (Node *root) {
  if (root == NULL) return;
  
  int maxL = maxLeftSpace (root);
  int maxR = maxRightSpace (root);
  int maxs = max (maxL, maxR);
  cout << maxL << " " << maxR << " " << maxs << "\n";
  queue <pair <Node *, int> > q; // Node *, space pair;
  q.push (make_pair (root, maxs));
  q.push (pair<Node*, int> (NULL, -1)); // delimeter

  int ch_count = 0;
  while (!q.empty ()) {
    auto p = q.front (); q.pop ();
    Node *node = p.first;
    int space = p.second;

    if (node == NULL && space == -1) {
      cout << "\n";
      ch_count = 0;
      if (!q.empty ()) q.push (p);
    }
    else {
      for (; ch_count < space; ++ch_count) cout << " ";
      cout << node->data;
      ch_count += 2;
      int lcrs = maxRightSpace (node->left);
      int rcls = maxLeftSpace (node->right);
      int cs = max (lcrs, rcls);
      if (node->left != NULL) q.push (make_pair (node->left, space - cs));
      if (node->right != NULL) q.push (make_pair (node->right, space + cs));
    }
  }
}
// 
// 18 26 L 18 27 R 19 28 L 19 29 R 20 30 L 20 31 R 21 32 L 21 33 R 22 34 L 22 35 R 23 36 L 23 37 R 24 38 L 24 39 R 25 40 L 25 41 R \

int main () {
#if 1
  string data =
    "\
     11 12 L 11 13 R							\
     12 14 L 12 15 R 13 16 L 13 17 R					\
     14 18 L 14 19 R 15 20 L 15 21 R 16 22 L 16 23 R 17 24 L 17 25 R	\
     -1 -1 L								\
    ";
  stringstream s (data);
  istream &is (s);
#else
  istream &is (cin);
#endif
  
  int n, p;
  char r;
  is >> p >> n >> r;
  map <int, Node*> m;
  Node *root = new Node (p);
  m[p] = root;
  do {
    m[n] = new Node (n);
    if (r == 'L') m[p]->left = m[n];
    else m[p]->right = m[n];
    is >> p >> n >> r;
  } while (n > 0 && p > 0 && (r == 'L' || r == 'R'));

  levelPrint (root);
  cout << "\n";
  prettyPrint (root);
}
