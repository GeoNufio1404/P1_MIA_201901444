const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const nodemon = require('nodemon');

const app = express();
const port = 3000;

app.use(bodyParser.json());
app.use(cors());

app.get('/', (req, res) => {
    res.send('Hello World!!');
    }
);

app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`);
    }
);

app.use('/admin', require('./Routes/Admin.routes'));
app.use("/usuario", require("./Routes/Usuario.routes"));
app.use("/recepcion", require("./Routes/Recepcion.routes"));

module.exports = app;