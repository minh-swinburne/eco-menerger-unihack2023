import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { UsageComponent } from './usage/usage.component';
import { DevicesComponent } from './devices/devices.component';
import { CostComponent } from './cost/cost.component';
import { PlansComponent } from './plans/plans.component';

const routes: Routes = [
  {
    path: '',
    component: HomeComponent,
    children: [
      {
        path: '',
        redirectTo: 'dashboard',
        pathMatch: 'full'
      },
      {
        path: 'dashboard',
        component: DashboardComponent
      },
      {
        path: 'cost',
        component: CostComponent
      },
      {
        path: 'devices',
        component: DevicesComponent
      },
      {
        path: 'plans',
        component: PlansComponent
      }
    ]
  },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
