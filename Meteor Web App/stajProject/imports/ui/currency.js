import { Template } from 'meteor/templating';
import { Mongo } from 'meteor/mongo';
import { CurrencyDB } from '../api/currencydb.js';
import './currency.html';

var listCurrency = [
  {
    value: 'TRY',
    text: 'Türk Lirası',
  },

  {
    value: 'USD',
    text: 'Amerikan Doları',
  },

  {
    value: 'EUR',
    text: 'Euro',
  },

  {
    value: 'RUB',
    text: 'Rus Rublesi',
  },

  {
    value: 'AED',
    text: 'Arap Emirlikleri Dirhemi',
  },



];

Template.currency.helpers({
  currencydb(){
    return CurrencyDB.find({});
  },

  showTheMessageBox(){
    return Session.get('showCurrencyMessageBox');
  },

  getOptions(){
    return listCurrency;
  },
});

Template.currency.events({
  'click #add-menu'(event){
    event.preventDefault();
    Session.set('showCurrencyMessageBox', true);
  },

  'click #addbox-add'(event, template){
    event.preventDefault();
    const sendFrom = template.find('#fromselect').value;
    const sendTo = template.find('#toselect').value;
    Meteor.call('currencydb.insert', sendFrom, sendTo, "--", "--", "--", function(error){
      if(error){
      switch (error.error) {
        case "same-currencies":
          alert("Aynı para biriminin karşılaştırması yapılamaz!");
          break;
        case "not-authorized":
          alert("Bu veriye erişebilmek için giriş yapmanız gerekmektedir.");
          break;
        case "already-added":
          alert("Eklemeye çalıştığınız çeviri, zaten ekli.");
          break;
        default:
          alert("Bilinmeyen hata!");
          break;
      }
    }
    });
    Session.set('showCurrencyMessageBox', false);
  },

  'click #addbox-cancel'(event){
    event.preventDefault();
    Session.set('showCurrencyMessageBox', false);
  },

  'click .currencylistItem'(event){
    var curId = this._id;

    Meteor.call('getCurrencyPrice', this.from, this.to, function(error, response){
      if(error){
        console.log("error", error);
        Meteor.call('currencydb.updateprice', curId, "Hata!");
      }else{
        Meteor.call('currencydb.updateprice', curId, response);
      }
    });

    Meteor.call('getCurrencyAmount', this.from, this.to, function(error, response){
      if(error){
        console.log("error", error);
        Meteor.call('currencydb.updateamount', curId, "Hata!");
      }else{
        Meteor.call('currencydb.updateamount', curId, response);
      }
    });

    Meteor.call('getCurrencyRate', this.from, this.to, function(error, response){
      if(error){
        console.log("error", error);
        Meteor.call('currencydb.updaterate', curId, "Hata!");
      }else{
        Meteor.call('currencydb.updaterate', curId, response);
      }
    });
  },
});
