#include <cstdlib>
#include <bits/stdc++.h>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  
  return getMinimax(state, depth);
}

Move getMinimax(State* state, int depth) {
  Move rt;
  int highestValue = INT_MIN;
  for (Move it : state->legal_actions) {
    int result = countMinimax(state->next_state(it), depth + 1);
    if (result > highestValue) {
      rt = it;
      highestValue = result;
    }
  }
  return rt;
}

int countMinimax(State* state, int depth) {
  int rt_max = INT_MIN;
  int rt_min = INT_MAX;

  if (!state->legal_actions.size()) {
    state->get_legal_actions();
    if (!state->legal_actions.size())
      return state->evaluate();
  }

  for (Move it : state->legal_actions) {
    if (depth == 3) return state->evaluate();
    else if (depth % 2 == 0) {
      int result = countMinimax(state->next_state(it), depth + 1);
      rt_max = rt_max > result ? rt_max : result;
    }
    else {
      int result = countMinimax(state->next_state(it), depth + 1);
      rt_min = rt_min < result ? rt_min : result;
    }
  }
  if (depth % 2 == 0) return rt_max;
  else return rt_min;
}