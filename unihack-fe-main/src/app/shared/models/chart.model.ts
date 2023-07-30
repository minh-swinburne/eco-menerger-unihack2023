import {
  ApexAxisChartSeries,
  ApexChart,
  ApexDataLabels,
  ApexMarkers,
  ApexTitleSubtitle,
  ApexFill,
  ApexYAxis,
  ApexXAxis,
  ApexTooltip,
  ApexStroke,
} from 'ng-apexcharts';

export interface MountainChart {
  series: ApexAxisChartSeries;
  chart: ApexChart;
  dataLabels: ApexDataLabels;
  markers: ApexMarkers;
  title: ApexTitleSubtitle;
  fill: ApexFill;
  yaxis: ApexYAxis;
  xaxis: ApexXAxis;
  tooltip: ApexTooltip;
  stroke: ApexStroke;
}
