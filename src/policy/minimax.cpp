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

int countMinimax(State* state, int depth, bool maxPlayer);

Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();

  int hScore = INT_MIN;
  Move rt;
  for (Move ns : state->legal_actions) {
    State* newState = state->next_state(ns);
    if (newState->game_state == WIN) continue;
    int result = countMinimax(newState, depth, false);
    if (result > hScore) {
      hScore = result;
      rt = ns;
    }
  }
  
  return rt;
}

int countMinimax(State* state, int depth, bool maxPlayer) {
  int rt;
  state->get_legal_actions();
  if (depth == 0 || !state->legal_actions.size()) {
    return state->evaluate();
  }
  if (maxPlayer) {
    rt = INT_MIN;
    for (auto ns : state->legal_actions) {
      State* newState = state->next_state(ns);
      if (newState->game_state == WIN) return INT_MIN;
      int result = countMinimax(newState, depth - 1, false);
      rt = rt > result ? rt : result;
    }
  }
  else {
    rt = INT_MAX;
    for (auto ns : state->legal_actions) {
      State* newState = state->next_state(ns);
      if (newState->game_state == WIN) return INT_MAX;
      int result = countMinimax(newState, depth - 1, true);
      rt = rt < result ? rt : result;
    }
  }
  return rt;
  /*int rt_max = INT_MIN;
  int rt_min = INT_MAX;

  if (!state->legal_actions.size()) {
    state->get_legal_actions();
    if (!state->legal_actions.size())
      return state->evaluate();
  }

  for (Move it : state->legal_actions) {
    if (depth == 5) return state->evaluate();
    else if (depth % 2 == 0) {
      int result = countMinimax(state->next_state(it), depth + 1, player ^ 1);
      rt_max = rt_max > result ? rt_max : result;
    }
    else {
      int result = countMinimax(state->next_state(it), depth + 1, player ^ 1);
      rt_min = rt_min < result ? rt_min : result;
    }
  }
  if (depth % 2 == 0) return rt_max;
  else return rt_min;*/
}