#include <bits/stdc++.h>
using namespace std;

/* Program to print binary tree in Tree format as follows:
** Following is the output of the program
** Pretty Print:

                               11
               12                              13
       14              15              16              17
   18      19      20      21      22      23      24      25
 26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41
**
*/

struct Node {
  Node (int data) : data (data) , left (NULL) , right (NULL) {}
  int data;
  Node *left, *right;
};

void levelOrderPrint (Node *root) {
  queue<Node *> q;
  q.push (root);
  q.push (NULL);
  while (!q.empty ()) {
    Node *node = q.front (); q.pop ();
    if (node == NULL) {
      cout << "\n";
      if (!q.empty ())
	q.push (NULL);
    }
    else {
      cout << node->data << " ";
      if (node->left != NULL) q.push (node->left);
      if (node->right != NULL) q.push (node->right);
    }
  }
}

// return x ^ n
int power (int x, int n) {
  if (n <= 0) return 1;
  int t = power (x, n/2);
  if (n%2 == 0) return t * t;
  return t * t * x;
}

// return max left and right levels
pair<int, int> maxLevels (Node *root, int sp = 0) {
  if (root == NULL) return make_pair (sp, sp);
  auto l = maxLevels (root->left, sp - 1);
  auto r = maxLevels (root->right, sp + 1);
  return make_pair (min (l.first, r.first), max(l.second, r.second));
}

int maxRightSpace (Node *root) {
  int level = maxLevels (root, 0).second - 2;
  if (level < 0) return 2;
  return power (2, level) * 4;
}

int maxLeftSpace (Node *root) {
  int level = abs(maxLevels (root, 0).second) - 2;
  if (level < 0) return 2;
  return power (2, level) * 4;
}

void prettyPrint (Node *root) {
  if (root == NULL) return;
  
  int maxL = maxLeftSpace (root);
  int maxR = maxRightSpace (root);
  int maxs = max (maxL, maxR);
  queue <pair <Node *, int> > q; // Node *, space pair;
  q.push (make_pair (root, maxs));
  q.push (pair<Node*, int> (NULL, -1)); // delimeter
  int ch_count = 1;
  
  while (!q.empty ()) {
    auto p = q.front (); q.pop ();
    Node *node = p.first;
    int space = p.second;

    if (node == NULL && space == -1) {
      cout << "\n";
      ch_count = 1;
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

int main () {
  string data =
    "\
     11 12 L 11 13 R							\
     12 14 L 12 15 R 13 16 L 13 17 R					\
     14 18 L 14 19 R 15 20 L 15 21 R 16 22 L 16 23 R 17 24 L 17 25 R	\
     18 26 L 18 27 R 19 28 L 19 29 R 20 30 L 20 31 R 21 32 L 21 33 R 22 34 L 22 35 R 23 36 L 23 37 R 24 38 L 24 39 R 25 40 L 25 41 R \
     -1 -1 L								\
    ";
  stringstream s (data);
  istream &is (s);
  
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

  levelOrderPrint (root);
  cout << "\n";
  prettyPrint (root);
}
