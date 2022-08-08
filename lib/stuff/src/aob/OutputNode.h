#pragma once

struct OutputNode {
  int patternIndex;
  int patternSize;
  bool isMatch = false;
  OutputNode* next = nullptr;
};
