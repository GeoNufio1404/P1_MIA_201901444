const express = require('express');             // npm install express || express sirve para crear un servidor
const cors = require('cors');                   // npm install cors || cors sirve para poder hacer peticiones desde el frontend
const bodyParser = require('body-parser');      // npm install body-parser || body-parser sirve para poder leer los datos que se envian desde el frontend
const nodemon = require('nodemon');             // npm install nodemon || nodemon sirve para reiniciar el servidor automaticamente
const morgan = require('morgan');               // npm install morgan || morgan sirve para ver las peticiones que se hacen al servidor

const routes_admin = require('./Routes/Admin.routes');
const routes_recepcion = require('./Routes/Recepcion.routes');
const routes_usuario = require('./Routes/Usuario.routes');

// Configuracion de Express
const app = express();
app.use(morgan('dev'));
app.use(cors({
    origin: '*',
    methods: ['GET', 'POST', 'PUT', 'DELETE'],
    allowedHeaders: ['Content-Type', 'Authorization']
}));

// Configuracion de Body Parser
app.use(bodyParser.urlencoded({ limit: '50mb', extended: true }));
app.use(bodyParser.json({ limit: '50mb' }));

app.get('/', (req, res) => {
    res.status(200).json({ message: 'Hello World!!' });
});

// Rutas
app.use('/admin', routes_admin);
app.use('/recepcion', routes_recepcion);
app.use('/usuario', routes_usuario);

module.exports = app;