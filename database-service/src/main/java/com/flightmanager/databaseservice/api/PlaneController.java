package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.PlaneModel;
import com.flightmanager.databaseservice.repos.PlaneRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Arrays;

@RestController
public class PlaneController {

    @Autowired
    private PlaneRepo repo;


    @GetMapping("${mapping.plane.get}")
    public ResponseEntity<ArrayList<PlaneModel>> getAll() {
        try{
            ArrayList<PlaneModel> models = (ArrayList<PlaneModel>) repo.findAll();
            return ResponseEntity.ok(models);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @GetMapping("${mapping.plane.get}/{id}")
    public ResponseEntity<PlaneModel> get(@PathVariable("id") long id) {
        try{
            PlaneModel model = repo.findById(id).orElse(null);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }
    @PostMapping("${mapping.plane.create}")
    public ResponseEntity<PlaneModel> get(@RequestBody PlaneModel data) {
        try{
            data.setId(0L);
            if(containsNullFields(data))
                return ResponseEntity.status(400).build();
            PlaneModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }
    @PostMapping("${mapping.plane.update}")
    public ResponseEntity<PlaneModel> update(@RequestBody PlaneModel data, @RequestParam("update") String update) {
        try{
            if(data.getId() == null)
                return ResponseEntity.status(400).build();
            PlaneModel fromDB = repo.findById(data.getId()).orElse(null);
            if(fromDB == null)
                return ResponseEntity.status(400).build();

            ArrayList<String> fields = new ArrayList<>(Arrays.asList(update.split(",")));
            if(!fields.contains("name"))
                data.setName(fromDB.getName());
            if(!fields.contains("pilot"))
                data.setPilot(fromDB.getPilot());
            if(!fields.contains("builtYear"))
                data.setBuiltYear(fromDB.getBuiltYear());
            if(!fields.contains("brokenPercentage"))
                data.setBrokenPercentage(fromDB.getBrokenPercentage());
            if(!fields.contains("speed"))
                data.setSpeed(fromDB.getSpeed());
            if(!fields.contains("minAirportSize"))
                data.setMinAirportSize(fromDB.getMinAirportSize());
            if(containsNullFields(data))
                return ResponseEntity.status(400).build();

            PlaneModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @DeleteMapping("${mapping.plane.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try{
            repo.deleteById(id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    private boolean containsNullFields(PlaneModel data){
        return data.getName() == null ||
                data.getPilot() == null ||
                data.getBuiltYear() == null ||
                data.getBrokenPercentage() != null ||
                data.getSpeed() == null ||
                data.getMinAirportSize() == null;
    }

}
