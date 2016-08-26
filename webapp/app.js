var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan'); //HTTP request logger
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
// https://nodejs.org/api/child_process.html
var execFile = require('child_process').execFile //run shell commands. Assync proc
var routes = require('./routes/index');
var app = express();

var left_right = 90;
var forward_backward = 45;
var claw = 0;
const INCREMENT_VALUE = 20;

//------------------------------------------------------------------------------
// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

// uncomment after placing your favicon in /public
//app.use(favicon(__dirname + '/public/favicon.ico'));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

//------------------------------------------------------------------------------
//Routes
app.use('/', routes);

app.get('/forward',function(req,res){
    forward_backward = forward_backward + INCREMENT_VALUE;
    //Child process/callback
    var child = execFile("./main", [left_right + "," + forward_backward + "," + claw], function (error, stdout, stderr) {
    });
    res.redirect('/');
})

app.get('/backward',function(req,res){
    forward_backward = forward_backward - INCREMENT_VALUE;
    //Child process/callback
    var child = execFile("./main", [left_right + "," + forward_backward + "," + claw], function (error, stdout, stderr) {
    });
    res.redirect('/');
})

app.get('/left',function(req,res){
    left_right = left_right - INCREMENT_VALUE;
    //Child process/callback
    var child = execFile("./main", [left_right + "," + forward_backward + "," + claw], function (error, stdout, stderr) {
    });
    res.redirect('/');
})

app.get('/right',function(req,res){
    left_right = left_right + INCREMENT_VALUE;
    //Child process/callback
    var child = execFile("./main", [left_right + "," + forward_backward + "," + claw], function (error, stdout, stderr) {
    });
    res.redirect('/');
})

app.get('/claw',function(req,res){
    if(claw == 0){
    	claw = 1;
    }
    else if(claw == 1){
    	claw = 0;
    }
    //Child process/callback
    var child = execFile("./main", [left_right + "," + forward_backward + "," + claw], function (error, stdout, stderr) {
    });
    res.redirect('/');
})

app.get('/reset',function(req,res){
    left_right = 90;
    forward_backward = 45;
    //Child process/callback
    var child = execFile("./main", [left_right + "," + forward_backward + "," + claw], function (error, stdout, stderr) {
    });
    res.redirect('/');
})

//------------------------------------------------------------------------------
// catch 404 and forward to error handler
app.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});
// error handlers
// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
    app.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});

module.exports = app;

