import { AfterViewInit, Component, ElementRef, OnInit, ViewChild } from '@angular/core';
import { AngularFireDatabase } from '@angular/fire/compat/database';


@Component({
  selector: 'app-devices',
  templateUrl: './devices.component.html',
  styleUrls: ['./devices.component.scss']
})
export class DevicesComponent {
  isOff: boolean = true;
  countingTime!: string;

  toggleState() {
    this.isOff = !this.isOff;
  }

  dateTime!: any
  report;
  status;
  constructor(db: AngularFireDatabase) {
    this.report = db.object('monthly_reports/1');
    this.status = db.object('Device1');
  }

  addReport() {
    const date = new Date(this.dateTime);
    const formattedDate = `${date.getMinutes()}:${date.getHours()} - ${date.getDate()}:${date.getMonth() + 1}:${date.getFullYear()}`;

    this.status.update({ offTime: formattedDate })
      .then(() => {
        console.log("Update successfully")
        this.dateTime = formattedDate
      });
  }

  toggleStatus() {
    this.status.update({ isOff: true })
      .then(() => {
        console.log("Update successfully")
      });
  }
}