// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char operation) {
  switch (operation) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
      return 2;
    case '-':
      return 2;
    case '/':
      return 3;
    case '*':
      return 3;
    case ' ':
      return 5;
    default:
      return 4;
  }
}

int calculate(char operation, int per1, int per2) {
  switch (operation) {
      case '+':
        return per2 + per1;
      case '-':
        return per2 - per1;
      case '*':
        return per1 * per2;
      case '/':
        if (per1 != 0)
          return per2 / per1;
      default:
        return 0;
  }
}

std::string infx2pstfx(std::string inf) {
  std::string post;
  char prob = ' ';
  TStack <char, 100> stack1;
  for (int i = 0; i < inf.size(); i++) {
    if (prior(inf[i]) == 4) {
      post.push_back(inf[i]);
      post.push_back(prob);
    } else {
      if (prior(inf[i]) == 0) {
        stack1.push(inf[i]);
      } else if (stack1.isEmpty()) {
        stack1.push(inf[i]);
      } else if ((prior(inf[i]) > prior(stack1.get()))) {
        stack1.push(inf[i]);
      } else if (prior(inf[i]) == 1) {
        while (prior(stack1.get()) != 0) {
          post.push_back(stack1.get());
          post.push_back(prob);
          stack1.pop();
        }
        stack1.pop();
      } else {
        while (!stack1.isEmpty() && (prior(inf[i]) <= prior(stack1.get()))) {
          post.push_back(stack1.get());
          post.push_back(prob);
          stack1.pop();
        }
        stack1.push(inf[i]);
      }
    }
  }
  while (!stack1.isEmpty()) {
    post.push_back(stack1.get());
    post.push_back(prob);
    stack1.pop();
  }
  for (int j = 0; j < post.size(); j++) {
    if (post[post.size()-1] == ' ')
      post.erase(post.size()-1);
  }
  return post;
}

int eval(std::string pref) {
  TStack <int, 100> stack2;
  int result = 0;
  for (int i = 0; i < pref.size(); i++) {
    if (prior(pref[i]) == 4) {
      stack2.push(pref[i] - '0');
    } else if (prior(pref[i]) < 4) {
      int a = stack2.get();
      stack2.pop();
      int b = stack2.get();
      stack2.pop();
      stack2.push(calculate(pref[i], a, b));
    }
  }
  result = stack2.get();
  return result;
}
