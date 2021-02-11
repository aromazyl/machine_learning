/*
 * kdtree.cc
 * Copyright (C) 2021 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "kdtree.h"


void KdTree::build(const std::vector<Data>& data) {
  this->root = new KdTreeNode();
  root->parent = NULL;
  root->left = NULL;
  root->right = NULL;
  std::queue<KdTreeNode*> cur_nodes;
  cur_nodes.push(root);
  size_t fea_size = data[0].feas.size();
  for (uint32_t i = 0; i < data.size(); ++i) {
    root->datas.push_back(i);
  }
  while (!cur_nodes.empty()) {
    auto* node = cur_nodes.front();
    cur_nodes.pop();
    split_node(node, kMinSubNodeNums, (split_fea+1) % fea_size);
    if (node->left) {
      cur_nodes.push(node->left);
    }
    if (node->right) {
      cur_nodes.push(node->right);
    }
  }
}

namespace {
  struct byDim {
    byDim(std::vector<Data>* datas, int dim): _datas(datas), _dim(dim) {}
    bool operator()(uint32_t x, uint32_t y) const {
      return (*_datas)[x].feas[_dim] < (*_datas)[y].feas[_dim];
    }
    int _dim;
    std::vector<Data>* _datas;
  };

  void sortby_dim(std::vector<Data>* datas, std::vector<uint32_t>& data_idx, int fea_dim) {
    sort(data.begin(), data.end(), byDim(datas, fea_dim));
  }
}

void KdTree::split_node(KdTreeNode* node, int min_sub_nod_nums, int fea_dim) {
  if (node->datas.size() <= min_sub_nod_nums) return;
  node->split_fea = fea_dim;
  node->left = new KdTreeNode();
  node->right = new KdTreeNode();
  sortby_dim(&(this->datas), node->datas, fea_dim);
  int mid = (node->datas.size() >> 1);
  double split_val = (datas[node->datas[mid]].feas[fea_dim] + datas[node->datas[mid+1]].feas[fea_dim]) / 2.0;
  node->split_fea = fea_dim;
  node->split_val = split_val;
  for (size_t i = 0; i < node->datas.size(); ++i) {
    if (i <= mid) {
      node->left->datas.push_back(i);
    } else {
      node->right->datas.push_back(i);
    }
  }
}

void KdTree::destroy() {
  std::queue<KdTreeNode*> nodes;
  nodes.push(root);
  while (!nodes.empty()) {
    auto* nd = nodes.front();
    nodes.pop();
    if (nd->left)
      nodes.push(nd->left);
    if (nd->right)
      nodes.push(nd->right);
    free(nd);
  }
}

