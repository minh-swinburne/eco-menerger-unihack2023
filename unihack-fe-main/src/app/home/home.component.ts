import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss'],
})
export class HomeComponent {
  navigators = [
    {
      id: 1,
      name: "Dashboard",
      svgPath: "../../assets/icons/dashboard.svg",
      path: "/dashboard"
    },
    {
      id: 2,
      name: "Cost",
      svgPath: "../../assets/icons/cost.svg",
      path: "/cost"
    },
    {
      id: 5,
      name: "Devices",
      svgPath: "../../assets/icons/emissions.svg",
      path: "/devices"
    },
    {
      id: 6,
      name: "Plans",
      svgPath: "../../assets/icons/emissions.svg",
      path: "/plans"
    }
  ]
}
