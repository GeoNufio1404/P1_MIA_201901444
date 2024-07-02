const { Router } = require("express")
const { check } = require('express-validator')

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

router.post('/Usuarios',
    [
        check('Nombre', 'El nombre es obligatorio').notEmpty(),
        check('Usuario', 'El usuario es obligatorio').notEmpty(),
        check('Correo', 'El correo es obligatorio').isEmail(),
        check('Password', 'El password es obligatorio').notEmpty(),
        check('TipoUsuario', 'El tipo de usuario es obligatorio').notEmpty(),
        validate
    ],
    AdminController.NuevoUsuario
);

router.get('/Usuarios', AdminController.ListarUsuarios);

module.exports = router;