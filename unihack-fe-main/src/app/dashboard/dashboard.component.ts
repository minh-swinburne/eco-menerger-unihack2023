import { Component } from '@angular/core';
import {
  ApexAxisChartSeries,
  ApexChart,
  ApexTitleSubtitle,
  ApexDataLabels,
  ApexFill,
  ApexMarkers,
  ApexYAxis,
  ApexXAxis,
  ApexTooltip,
  ApexStroke,
} from 'ng-apexcharts';

import * as mock from '../mock/tenDayRecorded';
import { MountainChart } from '../shared/models/chart.model';
import { AngularFireDatabase } from '@angular/fire/compat/database';

const dataMock = mock.oneDayRecordedMock;

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.scss'],
})
export class DashboardComponent {
  listDevice: MountainChart[] = [];

  // series!: ApexAxisChartSeries;
  // chart!: ApexChart;
  // dataLabels!: ApexDataLabels;
  // markers!: ApexMarkers;
  // title!: ApexTitleSubtitle;
  // fill!: ApexFill;
  // yaxis!: ApexYAxis;
  // xaxis!: ApexXAxis;
  // tooltip!: ApexTooltip;
  // stroke!: ApexStroke;
  device1:any;
  device2:any;

  constructor(db: AngularFireDatabase) {
    db.object('Device1').valueChanges().subscribe((value: any) => {
      this.device1 = value;
    });
    db.object('Device2').valueChanges().subscribe((value: any) => {
      this.device2 = value;
    });
    setTimeout(() => {
      this.renderListDevice();
    }, 3000);

  }

  public async renderListDevice() {
    this.initChartData({
      nameDevice: "Device 1",
      history: this.device1
    });
    // this.initChartData(this.fetchDB2);
  }

  public initChartData(device: any): void {
    let tempHistory = device.history;

    console.log(device.history, 'camnx');

    var historyData = Object.keys(tempHistory.History)
    .map(function(key) {

      let d = new Date(key)
        return {
          dateTime: d.getFullYear() + "-" + ('0' + (d.getMonth()+1)).slice(-2) + "-" + ('0' + d.getDate()).slice(-2)  +  " " + ('0' + d.getHours()).slice(-2) + ":" + ('0' + d.getMinutes()).slice(-2),
          value:  tempHistory.History[key].Value
        }
    });


    let dates = [];
    for (let i = 0; i < historyData.length; i++) {
      let t = new Date()
      t.setDate(new Date().getDate() - 1)
      if (new Date(historyData[i].dateTime).getTime() < t.getTime()) {
        continue
      }
      dates.push([historyData[i].dateTime, historyData[i].value]);
    }
    let oneItem: MountainChart = {
      series: [
        {
          name: 'Electric usage',
          data: dates,
          color: '#D1F248',
        },
      ],
      chart: {
        type: 'area',
        stacked: false,
        height: 350,

        zoom: {
          type: 'x',
          enabled: false,
          autoScaleYaxis: false,
        },
      },
      dataLabels: {
        enabled: false,
        style: {
          colors: ['#F44336', '#E91E63', '#9C27B0'],
        },
      },
      markers: {
        size: 0,
      },
      title: {
        text: 'Energy usage today of ' + device.nameDevice,
        align: 'left',
        style: {
          color: 'white',
          fontSize: '12px',
          fontWeight: '300',
        },
      },
      fill: {
        type: 'gradient',
        gradient: {
          shadeIntensity: 1,
          inverseColors: false,
          opacityFrom: 0.5,
          opacityTo: 0,
          stops: [0, 90, 100],
        },
      },
      stroke: {
        width: 1, // Set the width to a smaller value to make the line thinner
      },
      yaxis: {
        labels: {
          style: {
            colors: 'white',
          },
          formatter: function (val) {
            return val.toFixed(0);
          },
        },
        title: {
          text: 'kWh',
          style: {
            color: 'white',
            fontWeight: '300',
            fontSize: '10px',
          },
        },
      },
      xaxis: {
        labels: {
          format: 'HH:mm',
          style: {
            colors: 'white',
            fontWeight: '100',
            fontSize: '10px',
          },
        },
        type: 'datetime',
        tooltip: {
          formatter: function (value) {
            return new Date(value).toLocaleTimeString();
          }
        }
      },
      tooltip: {
        theme: 'dark',
        shared: false,
        y: {
          formatter: function (val) {
            return val.toFixed(0);
          },
        },
      },
    };

    this.listDevice.push(oneItem);
  }
}
