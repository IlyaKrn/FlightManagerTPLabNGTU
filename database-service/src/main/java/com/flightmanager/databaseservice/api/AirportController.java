package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.AirportModel;
import com.flightmanager.databaseservice.models.AirportModel;
import com.flightmanager.databaseservice.models.AirportModel;
import com.flightmanager.databaseservice.models.DispatcherModel;
import com.flightmanager.databaseservice.repos.AirportRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Arrays;

@RestController
public class AirportController {

    @Autowired
    private AirportRepo repo;


    @GetMapping("${mapping.airport.get}")
    public ResponseEntity<ArrayList<AirportModel>> getAll() {
        try{
            ArrayList<AirportModel> models = (ArrayList<AirportModel>) repo.findAll();
            return ResponseEntity.ok(models);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @GetMapping("${mapping.airport.get}/{id}")
    public ResponseEntity<AirportModel> get(@PathVariable("id") long id) {
        try{
            AirportModel model = repo.findById(id).orElse(null);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }
    @PostMapping("${mapping.airport.create}")
    public ResponseEntity<AirportModel> get(@RequestBody AirportModel data) {
        try{
            data.setId(0L);
            if(containsNullFields(data))
                return ResponseEntity.status(400).build();
            AirportModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.airport.update}")
    public ResponseEntity<AirportModel> update(@RequestBody AirportModel data, @RequestParam("update") String update) {
        try{
            if(data.getId() == null)
                return ResponseEntity.status(400).build();
            AirportModel fromDB = repo.findById(data.getId()).orElse(null);
            if(fromDB == null)
                return ResponseEntity.status(400).build();

            ArrayList<String> fields = new ArrayList<>(Arrays.asList(update.split(",")));
            if(!fields.contains("name"))
                data.setName(fromDB.getName());
            if(!fields.contains("x"))
                data.setX(fromDB.getX());
            if(!fields.contains("y"))
                data.setY(fromDB.getY());
            if(!fields.contains("size"))
                data.setSize(fromDB.getSize());
            if(containsNullFields(data))
                return ResponseEntity.status(400).build();

            AirportModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @DeleteMapping("${mapping.airport.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try{
            repo.deleteById(id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    private boolean containsNullFields(AirportModel data){
        return data.getName() == null ||
                data.getX() == null ||
                data.getY() == null ||
                data.getSize() == null;
    }

}
