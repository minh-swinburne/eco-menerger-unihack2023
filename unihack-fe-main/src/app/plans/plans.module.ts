import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { PlansComponent } from './plans.component';


@NgModule({
  declarations: [PlansComponent],
  imports: [
    CommonModule,
  ],
  exports: [PlansModule]
})
export class PlansModule { }
