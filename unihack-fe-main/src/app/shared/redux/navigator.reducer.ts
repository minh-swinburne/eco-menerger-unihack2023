import { createAction, createReducer, on } from '@ngrx/store';
import { AppNavigator, AppState } from '../models/navigator.model';
import { retrieve } from './navigator.actions';

export const initialState : AppState = {
    navigators: [
        {
            id: 1,
            name: "Dashboard"
        },
        {
            id: 2,
            name: "Cost"
        },
        {
            id: 3,
            name: "Appliances"
        },
        {
            id: 4,
            name: "Usage-by-rooms"
        },
        {
            id: 5,
            name: "Emissions"
        }
    ]
};

export const navigatorReducer = createReducer(
  initialState,
);
