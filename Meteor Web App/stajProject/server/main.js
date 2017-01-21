import { Meteor } from 'meteor/meteor';
import { check } from 'meteor/check';
import '../imports/api/maingrid.js';
import '../imports/api/weatherdb.js';
import '../imports/api/currencydb.js';
import '../imports/api/newsdb.js';

Meteor.startup(() => {

  var Future = Npm.require('fibers/future');
  var cheerio = Meteor.npmRequire('cheerio');

  Meteor.methods({

    //WEATHER STARTS

    getWeatherImage: function(cityToGet){
      check(cityToGet, String);

      var future = new Future();

      HTTP.get("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=" + cityToGet, {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#curIcon > img').attr('src');
          future.return(resp);
        }
      });
      return future.wait();

    },

    getWeatherTemp: function(cityToGet){
      check(cityToGet, String);

      var future = new Future();

      HTTP.get("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=" + cityToGet, {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#curTemp > span > span.wx-value').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    getWeatherHigh: function(cityToGet){
      check(cityToGet, String);

      var future = new Future();

      HTTP.get("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=" + cityToGet, {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#todaySummary > div:nth-child(1) > div:nth-child(2) > strong.high').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    getWeatherLow: function(cityToGet){
      check(cityToGet, String);

      var future = new Future();

      HTTP.get("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=" + cityToGet, {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#todaySummary > div:nth-child(1) > div:nth-child(2) > strong.low').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    getWeatherPressure: function(cityToGet){
      check(cityToGet, String);

      var future = new Future();

      HTTP.get("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=" + cityToGet, {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#current > div.show-for-large-up.large-3.columns.cc2 > table > tbody > tr:nth-child(1) > td:nth-child(2) > span > span > span.wx-value').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    getWeatherHumidty: function(cityToGet){
      check(cityToGet, String);

      var future = new Future();

      HTTP.get("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=" + cityToGet, {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#current > div.show-for-large-up.large-3.columns.cc2 > table > tbody > tr:nth-child(5) > td:nth-child(2) > span > span.wx-value').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    getWeatherRain: function(cityToGet){
      check(cityToGet, String);

      var future = new Future();

      HTTP.get("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=" + cityToGet, {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#current > div.show-for-large-up.large-3.columns.cc2 > table > tbody > tr:nth-child(6) > td:nth-child(2) > span > span.wx-value').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    //WEATHER ENDS
    //CURRENCY STARTS

    getCurrencyPrice: function(currencyFrom, currencyTo){
      check(currencyFrom, String);
      check(currencyTo, String);

      var future = new Future();
      HTTP.get("http://www.bloomberg.com/quote/"+ currencyFrom + currencyTo + ":CUR", {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#content > div > div > div.basic-quote > div > div.price-container > div.price').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    getCurrencyAmount: function(currencyFrom, currencyTo){
      check(currencyFrom, String);
      check(currencyTo, String);

      var future = new Future();
      HTTP.get("http://www.bloomberg.com/quote/"+ currencyFrom + currencyTo + ":CUR", {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#content > div > div > div.basic-quote > div > div.price-container > div.change-container > div:nth-child(1)').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    getCurrencyRate: function(currencyFrom, currencyTo){
      check(currencyFrom, String);
      check(currencyTo, String);

      var future = new Future();
      HTTP.get("http://www.bloomberg.com/quote/"+ currencyFrom + currencyTo + ":CUR", {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#content > div > div > div.basic-quote > div > div.price-container > div.change-container > div:nth-child(2)').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    //CURRENCY ENDS
    //NEWS STARTS

    getNewsImage: function(){
      var future = new Future();
      HTTP.get("http://www.ensonhaber.com/son-dakika/", {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#top > div.cleft > div.news-list.wide > ul > li:nth-child(1) > a > span.imgwrap > img').attr('src');
          future.return(resp);
        }
      });

      return future.wait();
    },

    getNewsTitle: function(){
      var future = new Future();
      HTTP.get("http://www.ensonhaber.com/son-dakika/", {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#top > div.cleft > div.news-list.wide > ul > li:nth-child(1) > a > span.ti').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    getNewsContent: function(){
      var future = new Future();
      HTTP.get("http://www.ensonhaber.com/son-dakika/", {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#top > div.cleft > div.news-list.wide > ul > li:nth-child(1) > span.spot').text();
          future.return(resp);
        }
      });

      return future.wait();
    },

    getNewsLink: function(){
      var future = new Future();
      HTTP.get("http://www.ensonhaber.com/son-dakika/", {}, function(error, response){
        if(error){
          future.return(error);
        }else{
          $ = cheerio.load(response.content);
          var resp = $('#top > div.cleft > div.news-list.wide > ul > li:nth-child(1) > a').attr('href');
          future.return(resp);
        }
      });

      return future.wait();
    },

    //NEWS ENDS

  });
});
