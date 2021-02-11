/*
 * kdtree.h
 * Copyright (C) 2021 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef KDTREE_H
#define KDTREE_H

struct Data {
  std::vector<double> feas;
  int data_index;
  double label;
};

struct KdTreeNode {
  std::vector<uint32_t> datas;
  KdTreeNode* parent;
  KdTreeNode* left;
  KdTreeNode* right;
  uint32_t split_fea;
  double split_val;
};

struct KdTree {
  const int kMinSubNodeNums = 100;
  KdTreeNode* root;
  void load_datas(std::vector<Data>& data);
  void build(const std::vector<Data>& data);
  void split_node(KdTreeNode* node, int min_sub_nod_nums, int fea_dim);
  void destroy();
};


#endif /* !KDTREE_H */
