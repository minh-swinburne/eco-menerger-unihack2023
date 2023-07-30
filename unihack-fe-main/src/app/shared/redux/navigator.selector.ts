import { createSelector } from '@ngrx/store';
import { AppState } from '../models/navigator.model';

export const selectNavigators = createSelector(
  (state: AppState) => state.navigators,
  (navigators) => navigators
);
