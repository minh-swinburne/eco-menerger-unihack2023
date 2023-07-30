import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { CostComponent } from './cost.component';

@NgModule({
  declarations: [CostComponent],
  imports: [
    CommonModule
  ],
  exports: [CostModule]
})
export class CostModule { }
