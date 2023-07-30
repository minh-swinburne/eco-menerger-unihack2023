import { createAction, props } from '@ngrx/store';
import { AppNavigator } from '../models/navigator.model';

export const retrieve = createAction(
  '[AppNavigator] Retrieve',
  props<{ navigators: AppNavigator[] }>()
);
