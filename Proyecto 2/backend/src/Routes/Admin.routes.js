const { Router } = require("express")
const { Check } = require('express-validator')

const validate = require("../middlewares/validateAtributes")
const AdminController = require("../controllers/admin.controller")

const router = Router();

router.get("/", (req, res) => {
    res.status(200).json(
        {
            msg: "Estoy en Admin"
        });
});

router.get("/ciclo_for/:numero", AdminController.ciclo_for);

router.post('/registro',
    [
        check('nombre', 'El nombre es obligatorio').notEmpty(),
        check('apellido', 'El apellido es obligatorio').notEmpty(),
        check('usuario', 'El usuario es obligatorio').notEmpty(),
        check('correo', 'El correo es obligatorio').isEmail(),
        check('password', 'El password es obligatorio').notEmpty(),
        validate
    ],
    AdminController.registro
)

module.exports = router;