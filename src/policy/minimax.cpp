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
  Move rt = *state->legal_actions.begin();
  for (Move ns : state->legal_actions) {
    State* newState = state->next_state(ns);
    if (newState->game_state == WIN && ns != *state->legal_actions.rbegin()) continue;
    int result = countMinimax(newState, depth, /*false*/true);
    if (result >= hScore) {
      hScore = result;
      rt = ns;
    }
  }
  
  return rt;
}

int countMinimax(State* state, int depth, bool maxPlayer) {
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if (depth == 0 || !state->legal_actions.size()) {
    return state->evaluate();
  }
  if (maxPlayer) {
    int rt = INT_MIN;
    for (auto ns : state->legal_actions) {
      State* newState = state->next_state(ns);
      if (newState->game_state == WIN) return INT_MIN;
      int result = countMinimax(newState, depth - 1, false);
      rt = rt > result ? rt : result;
    }
    return rt;
  }
  else {
    int rt = INT_MAX;
    for (auto ns : state->legal_actions) {
      State* newState = state->next_state(ns);
      if (newState->game_state == WIN) return INT_MAX;
      int result = countMinimax(newState, depth - 1, true);
      rt = rt < result ? rt : result;
    }
    return rt;
  }
}