import { Template } from 'meteor/templating';
import { Mongo } from 'meteor/mongo';
import { WeatherDB } from '../api/weatherdb.js';
import './weather.html';

var listWeather = [
  {
    type: 'weather',
    value: 'istanbul',
    text: 'İstanbul',
  },

  {
    type: 'weather',
    value: 'ankara',
    text: 'Ankara',
  },

  {
    type: 'weather',
    value: 'erzurum',
    text: 'Erzurum',
  },

  {
    type: 'weather',
    value: 'sivas',
    text: 'Sivas',
  },

  {
    type: 'weather',
    value: 'moskova',
    text: 'Moskova',
  },

  {
    type: 'weather',
    value: 'eskisehir',
    text: 'Eskişehir',
  },
];


Template.weather.helpers({
  weatherdb(){
    return WeatherDB.find({});
  },

  showTheMessageBox(){
    return Session.get('showWeatherMessageBox');
  },

  getOptions(){
    return listWeather;
  },
});

Template.weather.events({
  'click #add-menu'(event){
    event.preventDefault();
    Session.set('showWeatherMessageBox', true);
  },

  'click #addbox-add'(event, template){
    event.preventDefault();
    const data = template.find('#dataselect').value;
    Meteor.call('weatherdb.insert', "/img/weather-deneme.png", data, "--", "--", "--", "--", "--", "--", function(error){
      if(error){
                  switch (error.error) {
                    case "already-added":
                      alert("Eklemeye çalıştığınız bilgi, zaten ekli.");
                      break;
                    case "not-authorized":
                      alert("Bu veriye erişebilmek için giriş yapmanız gerekmektedir.");
                      break;
                    default:
                      alert("Bilinmeyen hata!");
                      break;
                  }
            }
        });
    Session.set('showWeatherMessageBox', false);
  },

  'click #addbox-cancel'(event){
    event.preventDefault();
    Session.set('showWeatherMessageBox', false);
  },

  'click .weatherlistItem'(event){
    var curId = this._id;

    //console.log(this.city);
    Meteor.call('getWeatherTemp', this.city, function(error, response){
      if(error){
        console.log("error", error);
        //Meteor.call('weatherdb.updatetemp', curId, "Hata!");
      }else{
        Meteor.call('weatherdb.updatetemp', curId, response);
      }
    });

    Meteor.call('getWeatherImage', this.city, function(error, response){
      if(error){
        console.log(error);
      }else{
        Meteor.call('weatherdb.updateimage', curId, response);
      }
    });

    Meteor.call('getWeatherHigh', this.city, function(error, response){
      if(error){
        console.log(error);
      }else{
        console.log(response);
        Meteor.call('weatherdb.updatehigh', curId, response);
      }
    });
    Meteor.call('getWeatherLow', this.city, function(error, response){
      if(error){
        console.log(error);
      }else{
        Meteor.call('weatherdb.updatelow', curId, response);
      }
    });
    Meteor.call('getWeatherPressure', this.city, function(error, response){
      if(error){
        console.log(error);
      }else{
        Meteor.call('weatherdb.updatepressure', curId, response);
      }
    });
    Meteor.call('getWeatherHumidty', this.city, function(error, response){
      if(error){
        console.log(error);
      }else{
        Meteor.call('weatherdb.updatehumidty', curId, response);
      }
    });
    Meteor.call('getWeatherRain', this.city, function(error, response){
      if(error){
        console.log(error);
      }else{
        Meteor.call('weatherdb.updaterain', curId, response);
      }
    });
  },

});
