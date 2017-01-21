import { Template } from 'meteor/templating';
import { ReactiveDict } from 'meteor/reactive-dict';
import { WeatherDB } from '../api/weatherdb.js';
import { CurrencyDB } from '../api/currencydb.js';
import { NewsDB } from '../api/newsdb.js';
import { MainGrid } from '../api/maingrid.js';

import './contentinside.js';
import './body.html'
import './home.js';
import './weather.js';
import './currency.js';
import './news.js';



Template.body.onCreated(function bodyOnCreated(){
  this.state = new ReactiveDict();
  Meteor.subscribe('maingriddb');
  Meteor.subscribe('weatherdb');
  Meteor.subscribe('currencydb');
  Meteor.subscribe('newsdb');
  Session.set('hiddenMenu', false);
  Session.set('whichPage', 2);
});

Template.body.helpers({
  hideMenu(){
    return Session.get('hiddenMenu');
  },

  /*isHome(){
    if(Session.get('whichPage') === 1){
      return true;
    }else{
      return false;
    }
  },
  */
  isWeather(){
    if(Session.get('whichPage') === 2){
      return true;
    }else{
      return false;
    }
  },

  isCurrency(){
    if(Session.get('whichPage') === 3){
      return true;
    }else{
      return false;
    }
  },

  isNews(){
    if(Session.get('whichPage') === 4){
      return true;
    }else{
      return false;
    }
  }

//mrb
});

Template.body.events({
  'click .openclose'(event){
    event.preventDefault();
    if(Session.get('hiddenMenu')){
      Session.set('hiddenMenu', false);
    }else{
      Session.set('hiddenMenu', true);
    }
  },

/*  'click #liHome'(event){
    Session.set('whichPage', 1);
  },*/

  'click #liWeather'(event){
    Session.set('whichPage', 2);
  },

  'click #liCurrency'(event){
    Session.set('whichPage', 3);
  },

  'click #liNews'(event){
    Session.set('whichPage', 4);
  },

  /*'click #liSocial'(event){
    Session.set('whichPage', 5);
  },*/
});
