const { validationResult } = require('express-validator'); // npm install express-validator || sirve para validar los datos que se envian al servidor

const validate = (req, res, next) => {
    const errors = validationResult(req);
    if (!errors.isEmpty()) {
        return res.status(400).json(errors);
    }
    next();
}

module.exports = validate;