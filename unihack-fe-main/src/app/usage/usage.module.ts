import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { UsageComponent } from './usage.component';



@NgModule({
  declarations: [UsageComponent],
  imports: [
    CommonModule
  ],
  exports: [UsageModule]
})
export class UsageModule { }
