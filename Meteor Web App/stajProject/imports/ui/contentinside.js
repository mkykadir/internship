import { Meteor } from 'meteor/meteor';
import { Template } from 'meteor/templating';
import { MainGrid } from '../api/maingrid.js';
import './contentinside.html';



Template.weatherinside.onCreated(function weatherinsideOnCreated(){
  Session.set("weatherCity", this.contentData);
});

Template.weatherinside.helpers({
  getImage: function(){
    var getData = Session.get("images");
    return getData;
  },

  getTemp: function(){
    var getData = Session.get("temps");
    return getData;
  }
});

Template.weatherinside.events({
  'click #refresh'(event, template){
    event.preventDefault();
    Meteor.call('getWeatherImage', this.contentData, function(error, result){
      if(error){
        console.log("error", error);
      }

      Session.set("images", result);
    });

    Meteor.call('getWeatherTemp', this.contentData, function(error, result){
      if(error){
        console.log("error", error);
      }

      Session.set("temps", result);
    });
  },
});
