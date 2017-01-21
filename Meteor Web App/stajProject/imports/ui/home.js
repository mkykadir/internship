import { Template } from 'meteor/templating';
import { Mongo } from 'meteor/mongo';
import { MainGrid } from '../api/maingrid.js';

import './home.html';


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
];

var listCurrency = [
  {
    type: 'currency',
    value: 'usdtry',
    text: 'USD <-> TRY',
  },

  {
    type: 'currency',
    value: 'eurtry',
    text: 'EUR <-> TRY',
  },

  {
    type: 'currency',
    value: 'usdeur',
    text: 'USD <-> EUR',
  },

];

var listNews = [
  {
    type: 'news',
    value: 'world',
    text: 'Dünya',
  },

  {
    type: 'news',
    value: 'tr',
    text: 'Türkiye',
  },

  {
    type: 'news',
    value: 'usa',
    text: 'Amerika',
  },

  {
    type: 'news',
    value: 'eu',
    text: 'Avrupa',
  },

  {
    type: 'news',
    value: 'as',
    text: 'Asya',
  },
];

var listSocial = [
  {
    type: 'social',
    value: 'twittertr',
    text: 'Twitter TR',
  },

  {
    type: 'social',
    value: 'twitterworld',
    text: 'Twitter Dünya',
  },
];

Template.home.helpers({
  maingriddb(){
    return MainGrid.find({});
  },

  showTheMessageBox(){
    return Session.get('showMessageBox');
  },

  getOptions(){
    switch (Session.get('type')) {
      case 'weather':
          return listWeather;
        break;
      case 'currency':
          return listCurrency;
        break;
      case 'news':
          return listNews;
          break;
      case 'social':
          return listSocial;
          break;
      default:
        //do nothing
    }
  }
});

Template.home.events({
  'click #add-menu'(event){
    event.preventDefault();
    Session.set('showMessageBox', true);
    Session.set('type', 'weather');
  },

  'click #addbox-add'(event, template){
    event.preventDefault();
    const type = template.find('#typeselect').value;
    const data = template.find('#dataselect').value;
    //const gettext = template.find('#dataselect').text;
    Meteor.call('maingriddb.insert', type, data);
    Session.set('showMessageBox', false);
  },

  'change #typeselect'(event, template){
    const type = template.find('#typeselect').value;
    Session.set('type', type);
  },

  'click #addbox-cancel'(event){
    event.preventDefault();
    Session.set('showMessageBox', false);
  },


});
