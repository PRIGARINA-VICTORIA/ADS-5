// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <map>
#include "tstack.h"
	int ShowPrior(char prior) {
	  switch(prior) {
	    case '(' : return 0;
	    case ')' : return 1;
	    case '+' : return 2;
	    case '-' : return 2;
	    case '*' : return 3;
	    case '/' : return 3;
	    default:
	      return -1;
	    }
	}
	

	int Execute(char operation, int first, int second) {
	  switch(operation) {
	    case '+' :
	      return first + second; 
	        break;
	    case  '-': 
	        first - second;
	        break;
	    case  '*':
	        first * second;
	        break;
	    case '/' :
	        first / second;
	        break;
	    }
	}
	

	std::string infx2pstfx(std::string inf) {
	  // добавьте код
	  char  start = 0;
	  TStack <char, 100> stack1;
	  std::string str;
	  for (int i = 0; i < inf.length(); i++) {
	    int Prior = ShowPrior(inf[i]);
	    if (Prior > -1) {
	      if ((Prior == 0 || Prior > ShowPrior(start) || stack1.isEmpty()) && inf[i] != ')') {
	        if (stack1.isEmpty()) 
	          start = inf[i];
	        stack1.push(inf[i]);
	      } else if (inf[i] == ')') {
	        while (stack1.get() != '(') {
	          str.push_back(stack1.get()); 
	          str.push_back(' ');
	          stack1.pop();
	        }
	        stack1.pop();
	        if (stack1.isEmpty())
	          start = 0;
	      } else {
	        while (!stack1.isEmpty() && ShowPrior(stack1.get()) >= Prior) {
	          str.push_back(stack1.get());
	          str.push_back(' ');
	          stack1.pop();
	        }
	        if (stack1.isEmpty())
	          start = inf[i];
	        stack1.push(inf[i]);
	      }
	    } else {
	      str.push_back(inf[i]);
	      str.push_back(' ');
	    }
	  }
	  while (!stack1.isEmpty()) {
	    str.push_back(stack1.get());
	    str.push_back(' ');
	    stack1.pop();
	  }
	  str.erase(str.end() - 1, str.end());
	  return str;
	}
	

	int eval(std::string post) {
	  // добавьте код
	  TStack <int, 100> stack2;
	  int res = 0, first= 0, second = 0;
	  for (int i = 0; i < post.length(); i++) {
	    if (ShowPrior(post[i] == -1)) {
	      stack2.push(post[i] - '0');
	      if (ShowPrior(post[i] > 1)) {
	        second = stack2.get();
	        stack2.pop();
	        first = stack2.get();
	        stack2.pop();
	        stack2.push(Execute(post[i], first, second));
	      }
	    }
	  }
	  res = stack2.get();
	  return res;
	}
