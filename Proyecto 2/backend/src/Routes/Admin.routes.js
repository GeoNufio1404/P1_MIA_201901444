const { Router } = require("express")
const AdminController = require("../controllers/admin.controller")

const router = Router()

router.get("/", (req, res) => {
    res.status(200).json({ message: "Estoy en Admin" })
});

router.get("/ciclo_for/:numero", AdminController.ciclo_for);

module.exports = router;